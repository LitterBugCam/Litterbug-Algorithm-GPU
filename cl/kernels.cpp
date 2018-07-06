#include "kernels.h"
#include <iostream>
#include "matproxy.h"

#define CL_HPP_ENABLE_EXCEPTIONS 1
#define CL_HPP_MINIMUM_OPENCL_VERSION 110
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_CL_1_2_DEFAULT_BUILD

//that is damn known bug... to make all proper, this include must be SINGLE in program
//so all CL code will have to stay here...
#include <CL/cl2.hpp>

static cl::Context clCont;
static cl::Device  clDev;
static cl::CommandQueue queue;
static cl::Program Kernels;
static int gpuUsed = 12;
static int Align = gpuUsed * 16;
//warning! I assume incoming memory is aligned to 16 * 12 !!! (12 cpus, 16 numbers per iteration in loop)
cl::Program getCompiledKernels()
{
    const static std::vector<std::string> source =
    {
        R"CLC(
        __kernel void cartToAngle(const int total, __global const float* gradx, __global const float* grady, __global float* radians)
        {
           private const size_t i        = get_global_id(0);
           private const size_t gpu_used = get_global_size(0);

           private const size_t elements_count = total / (gpu_used * 16);
           private const size_t offset = i * total / gpu_used;

            for (size_t k = 0; k < elements_count; ++k)
            {
               private float16 x = vload16( k , gradx + offset);
               private float16 y = vload16( k , grady + offset);
               vstore16(atan2(y, x) + 3.14159265f, k, radians + offset);
            }
        }
        )CLC",

        R"CLC(
        __kernel void gradMagic(const int total, const int is_deeper_magic, const float alpha_s, const float fore_th, __global const float* gradx, __global const float* grady,
                                                 //in/out
                                                 __global float* BSx,  __global float* BSy, __global int* mapRes)
        {
            private const size_t i        = get_global_id(0);
            private const size_t gpu_used = get_global_size(0);

            private const size_t elements_count = total / (gpu_used * 16);
            private const size_t offset = i * total / gpu_used;

            const int16 mult = is_deeper_magic; //all 1's or all 0's

            for (size_t k = 0; k < elements_count; ++k)
            {
               const float16 as = alpha_s;
               private float16 gx = vload16( k , gradx + offset);
               private float16 bx = vload16( k , BSx   + offset);

               float16 D_Sx = gx - bx;
               bx += D_Sx * as;
               vstore16(bx, k, BSx + offset);

               private float16 gy = vload16( k , grady + offset);
               private float16 by = vload16( k , BSy   + offset);

               float16 D_Sy = gy - by;
               by += D_Sy * as;
               vstore16(by, k, BSy + offset);
               int16 mr           = vload16( k , mapRes + offset);

               const float16 fth = fore_th;
               const float16 v19 = 19;

               mr -= mult;

               int16 c1 = isgreater(fabs(D_Sx), fth) && isgreater(fabs(gx), v19);
               int16 c2 = isgreater(fabs(D_Sy), fth) && isgreater(fabs(gy), v19);
               const int16 zeros = 0;
               const int16 ones  = 1;
               const int16 twos  = 2;
               const int16 twos5 = 255;

               mr += mult * select(zeros, ones, c2 || c1) * twos;


               c1 = mr < zeros;
               c2 = convert_int16(select(mr, zeros, c1));//overflow protection
               c1 = c2 > twos5;
               mr = convert_int16(select(c2, twos5, c1)); //overflow protection

               vstore16(mr, k, mapRes + offset);
            }
        }
        )CLC",
    };

    cl::Program progs(source);
    try
    {
#ifndef NO_FPS
        std::cout << "Building kernels..." << std::endl;
#endif
        progs.build();
    }
    catch (...)
    {
        std::cerr << "Failed to compiler kernels: " << std::endl;
        // Print build info for all devices
        cl_int buildErr = CL_SUCCESS;
        auto buildInfo = progs.getBuildInfo<CL_PROGRAM_BUILD_LOG>(&buildErr);
        for (auto &pair : buildInfo)
            std::cerr << pair.second << std::endl << std::endl;
        exit(255);
    }
#ifndef NO_FPS
    std::cout << "Kernels are compiled..." << std::endl;
#endif

    return progs;
}

openCl::openCl()
{
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    cl::Platform plat;
    for (const auto &p : platforms)
    {
        std::string platver = p.getInfo<CL_PLATFORM_VERSION>();
        if (platver.find("OpenCL") != std::string::npos)
        {
            plat = p;
            std::cout << "Using platform: " << platver << std::endl;
            break;
        }
    }

    if (plat() == nullptr)
    {
        std::cerr << "No OpenCL platform found.";
        exit(255);
    }
    cl::Platform newP = cl::Platform::setDefault(plat);
    if (newP != plat)
    {
        std::cerr << "Error setting default platform.";
        exit(255);
    }
    try
    {
        std::vector<cl::Device> dlist;
        plat.getDevices(CL_DEVICE_TYPE_GPU, &dlist);
        if (!dlist.size())
        {
            std::cerr << "Error - no GPU detected.";
            exit(255);
        }
        clDev = dlist.at(0);
        cl::Device::setDefault(clDev);
        clCont = cl::Context(clDev);
        cl::Context::setDefault(clCont);
        // Default command queue, also passed in as a parameter
        queue = cl::CommandQueue(clCont, clDev);
        cl::CommandQueue::setDefault(queue);
    }
    CATCHCL
    Align = gpuUsed * 16;
    Kernels = getCompiledKernels();
}

void openCl::atan2(cv::Mat &x, cv::Mat &y, cv::Mat &angle)
{

    const auto xs = x.rows * x.cols;
    const auto ys = y.rows * y.cols;
    assert(xs == ys);
    MatProxy<float> px(x, 1, Align);
    MatProxy<float> py(y, 1, Align);
    MatProxy<float> pa(angle, x.rows, x.cols, Align);

    try
    {
        auto kernel = cl::KernelFunctor<const int32_t, cl::Buffer&, cl::Buffer&, cl::Buffer&>(Kernels, "cartToAngle");
        cl::Buffer bx(queue, px.r_ptr(), px.end(), true, true);
        cl::Buffer by(queue, py.r_ptr(), py.end(), true, true);
        cl::Buffer ba(queue, pa.w_ptr(), pa.end(), false, true);
        //https://jorudolph.wordpress.com/2012/02/03/opencl-work-item-ids-globalgrouplocal/
        kernel(cl::EnqueueArgs(queue, cl::NDRange(gpuUsed), cl::NDRange(1)), px.sizeAligned(), bx, by, ba).wait();
        cl::copy(ba, pa.w_ptr(), pa.end());
    }
    CATCHCL
    pa.updateMatrixIfNeeded();

}

void openCl::magic(bool is_deeper_magic, const float alpha_s, const float fore_th, cv::Mat &gradx, cv::Mat &grady, cv::Mat &bx, cv::Mat &by, cv::Mat& mapR)
{
    static MatProxy<float> pgx(Align);
    pgx.assign(gradx, 0);
    static MatProxy<float> pgy(Align);
    pgy.assign(grady, 0);
    static MatProxy<float> pbx(Align);
    pbx.assign(bx, 0);
    static MatProxy<float> pby(Align);
    pby.assign(by, 0);
    static MatProxy<uint8_t, int> pres(Align);
    pres.assign(mapR, 0);

    try
    {
        auto kernel = cl::KernelFunctor<const int, int, float, float, cl::Buffer&, cl::Buffer&, cl::Buffer&, cl::Buffer&, cl::Buffer&>(Kernels, "gradMagic");
        cl::Buffer bpgx(queue, pgx.r_ptr(),   pgx.end(),  true,  true);
        cl::Buffer bpgy(queue, pgy.r_ptr(),   pgy.end(),  true,  true);
        cl::Buffer bbx( queue, pbx.r_ptr(),   pbx.end(),  false, true);
        cl::Buffer bby( queue, pby.r_ptr(),   pby.end(),  false, true);
        cl::Buffer bres(queue, pres.r_ptr(),  pres.end(), false, true);

        kernel(cl::EnqueueArgs(queue, cl::NDRange(gpuUsed), cl::NDRange(1)), pgx.sizeAligned(), (is_deeper_magic) ? 1 : 0, alpha_s, fore_th, bpgx, bpgy, bbx, bby, bres).wait();
        cl::copy(bbx,  pbx.w_ptr(),  pbx.end());
        cl::copy(bby,  pby.w_ptr(),  pby.end());
        cl::copy(bres, pres.w_ptr(), pres.end());
    }
    CATCHCL

    pbx.updateMatrixIfNeeded();
    pby.updateMatrixIfNeeded();
    pres.updateMatrixIfNeeded();
    //    for (int i = 0; i < 16; ++i)
    //        std::cout << *(pgx.w_ptr() + i + mapR.cols * 20 + 50) << " ";
    //    std::cout << std::endl;
}
