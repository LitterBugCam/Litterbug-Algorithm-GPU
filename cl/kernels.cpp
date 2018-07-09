#include "kernels.h"
#include <iostream>
#include "matproxy.h"
#include <chrono>

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

//VC4C compiler does invalid division on PI
static float gpu1 = 1.f / gpuUsed;
static float gpu16 = 1.f / Align;

//warning! I assume incoming memory is aligned to 16 * 12 !!! (12 cpus, 16 numbers per iteration in loop)
cl::Program getCompiledKernels()
{
    const static std::string support_funcs = R"CLC(
                                             float16 myselectf16(float16 afalse, float16 atrue, int16 condition)
                                             {
                                                 //we have -1 = true in condition ...it should be so
                                                 float16 cond = -1.f * convert_float16(condition);
                                                 float16 not_cond = 1.f - cond;
                                                 return atrue * cond + afalse * not_cond;
                                             }

                                             int16 myselecti16(int16 afalse, int16 atrue, int16 condition)
                                             {
                                                 //we have -1 = true in condition ...it should be so
                                                 int16 cond     = -1 * condition;
                                                 int16 not_cond = 1 - cond;
                                                 return atrue * cond + afalse * not_cond;
                                             }
                                             //nvidia ref. impl.: http://developer.download.nvidia.com/cg/atan2.html
                                             float16 myatan2f16(float16 y, float16 x)
                                             {
                                               float16 t0, t1, t2, t3, t4;

                                               t3 = fabs(x);
                                               t1 = fabs(y);
                                               t0 = max(t3, t1);
                                               t1 = min(t3, t1);
                                               t3 = 1.f / t0;
                                               t3 = t1 * t3;

                                               t4 = t3 * t3;
                                               t0 =         - 0.013480470f;
                                               t0 = t0 * t4 + 0.057477314f;
                                               t0 = t0 * t4 - 0.121239071f;
                                               t0 = t0 * t4 + 0.195635925f;
                                               t0 = t0 * t4 - 0.332994597f;
                                               t0 = t0 * t4 + 0.999995630f;
                                               t3 = t0 * t3;

                                               t3 = (fabs(y) > fabs(x)) ? 1.570796327f - t3 : t3;
                                               t3 = (x < 0) ?  3.141592654f - t3 : t3;
                                               t3 = (y < 0) ? -t3 : t3;

                                               return t3;
                                             }

                                             //nvidia ref. impl.: http://developer.download.nvidia.com/cg/atan2.html
                                             float myatan2f1(float y, float x)
                                             {
                                               float t0, t1, t2, t3, t4;

                                               t3 = fabs(x);
                                               t1 = fabs(y);
                                               t0 = max(t3, t1);
                                               t1 = min(t3, t1);
                                               t3 = 1.f / t0;
                                               t3 = t1 * t3;

                                               t4 = t3 * t3;
                                               t0 =         - 0.013480470f;
                                               t0 = t0 * t4 + 0.057477314f;
                                               t0 = t0 * t4 - 0.121239071f;
                                               t0 = t0 * t4 + 0.195635925f;
                                               t0 = t0 * t4 - 0.332994597f;
                                               t0 = t0 * t4 + 0.999995630f;
                                               t3 = t0 * t3;

                                               t3 = (fabs(y) > fabs(x)) ? 1.570796327f - t3 : t3;
                                               t3 = (x < 0) ?  3.141592654f - t3 : t3;
                                               t3 = (y < 0) ? -t3 : t3;

                                               return t3;
                                             }


    )CLC";
    const static std::vector<std::string> source =
    {
        support_funcs,
        R"CLC(


        __kernel void cartToAngle(const int total, float gpu16, float gpu1, __global const float* restrict gradx, __global const float* restrict grady, __global float* restrict radians)
        {
            private const size_t i        = get_global_id(0);
            private const size_t gpu_used = get_global_size(0);

            private const int elements_count = (int)(total * gpu16); //total / (gpu_used * 16);
            private const int offset = (int)(i * total * gpu1);      //i * total / gpu_used;

            const float16 pi2 = 2 * 3.14159265f;
            for (size_t k = 0; k < elements_count; ++k)
            {
               private float16 x = vload16( k , gradx + offset);
               private float16 y = vload16( k , grady + offset);
               float16 a  = myatan2f16(y, x);
               //a = fmod(a + pi2, pi2); //on nvidia myselectf16 works faster then fmod
               a = myselectf16(a, a + pi2, a < 0);
               vstore16(a, k, radians + offset);
            }
        }
        )CLC",

        R"CLC(

        __kernel void gradMagic(const int total, float gpu16, float gpu1, const int is_deeper_magic, const float alpha_s, const float fore_th, __global const float* gradx, __global const float* grady,
                                                 //in/out
                                                 __global float* BSx,  __global float* BSy, __global int* mapRes)
        {
            private const size_t i        = get_global_id(0);
            private const size_t gpu_used = get_global_size(0);

            private const int elements_count = (int)(total * gpu16); //total / (gpu_used * 16);
            private const int offset = (int)(i * total * gpu1);      //i * total / gpu_used;

            const int16 mult = is_deeper_magic; //all 1's or all 0's



            for (int k = 0; k < elements_count; ++k)
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
               c2 = myselecti16(mr, zeros, c1);//overflow protection
               c1 = c2 > twos5;
               mr = myselecti16(c2, twos5, c1); //overflow protection

               vstore16(mr, k, mapRes + offset);

            }
        }
        )CLC",
        R"CLC(
        __kernel void SobelDetector( __global const uchar* restrict input,  __global float* restrict grad_x,  __global float* restrict grad_y,  __global float* restrict grad_dir)
        {
            uint x      = get_global_id(0);
            uint y      = get_global_id(1);
            uint width  = get_global_size(0);
            uint height = get_global_size(1);
            float Gx = (0);
            float Gy = (0);
            // Given that we know the (x,y) coordinates of the pixel we're
            // looking at, its natural to use (x,y) to look at its
            // neighbouring pixels
            // Convince yourself that the indexing operation below is
            // doing exactly that
            // the variables i00 through to i22 seek to identify the pixels
            // following the naming convention in graphics programming e.g.
            // OpenGL where i00 refers
            // to the top-left-hand corner and iterates through to the bottom
            // right-hand corner
            if( x >= 1 && x < (width-1) && y >= 1 && y < height - 1)
            {
                float i00 = convert_float(input[(x - 1) + (y - 1) * width]);
                float i10 = convert_float(input[x + (y - 1) * width]);
                float i20 = convert_float(input[(x + 1) + (y - 1) * width]);
                float i01 = convert_float(input[(x - 1) + y * width]);
                float i11 = convert_float(input[x + y * width]);
                float i21 = convert_float(input[(x + 1) + y * width]);
                float i02 = convert_float(input[(x - 1) + (y + 1) * width]);
                float i12 = convert_float(input[x + (y + 1) * width]);
                float i22 = convert_float(input[(x + 1) + (y + 1) * width]);
                // To understand why the masks are applied this way, look
                // at the mask for Gy and Gx which are respectively equal
                // to the matrices:
                // { {-1, 0, 1}, { {-1,-2,-1},
                // {-2, 0, 2}, { 0, 0, 0},
                // {-1, 0, 1}} { 1, 2, 1}}
                uint out_index = x + y *width;
                float Gx = i00 + (float)(2) * i10 + i20 - i02 - (float)(2) * i12 -i22;
                float Gy = i00 - i20 + (float)(2)*i01 - (float)(2)*i21 + i02 - i22;

                grad_x[out_index] = Gx;
                grad_y[out_index] = Gy;
                float a = myatan2f1(Gy, Gx);
                if ( a < 0) a += 6.2831853f;
                grad_dir[out_index] = a;
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
        //progs.build("-cl-opt-disable");
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

    gpu1  = 1.f / gpuUsed;
    gpu16 = 1.f / Align;


    Kernels = getCompiledKernels();
}

openCl::~openCl()
{
}

void openCl::atan2(cv::Mat &gradx, cv::Mat &grady, cv::Mat &angle)
{
    const auto xs = gradx.rows * gradx.cols;
    const auto ys = grady.rows * grady.cols;
    assert(xs == ys);
    static MatProxy<float> px(Align);
    px.assign(gradx, 0);
    static MatProxy<float> py(Align);
    py.assign(grady, 0);
    static MatProxy<float> pa(Align);
    pa.assign(angle, gradx.rows, gradx.cols);

    try
    {
        auto kernel = cl::KernelFunctor<const int32_t, float, float, cl::Buffer&, cl::Buffer&, cl::Buffer&>(Kernels, "cartToAngle");
        cl::Buffer bx(queue, px.r_ptr(), px.end(), true, true);
        cl::Buffer by(queue, py.r_ptr(), py.end(), true, true);
        cl::Buffer ba(queue, pa.w_ptr(), pa.end(), false, true);
        //https://jorudolph.wordpress.com/2012/02/03/opencl-work-item-ids-globalgrouplocal/
        kernel(cl::EnqueueArgs(queue, cl::NDRange(gpuUsed), cl::NDRange(gpuUsed)), px.sizeAligned(),  gpu16, gpu1, bx, by, ba).wait();
        cl::copy(ba, pa.w_ptr(), pa.end());
    }
    CATCHCL
    pa.updateMatrixIfNeeded();

    //    const auto deltaa = 10 * gradx.cols + 50;
    //    for (auto i = 0; i < 16; ++i)
    //        std::cout << "x = " << *(px.w_ptr() + i + deltaa) << "; y = " << *(py.w_ptr() + i + deltaa) << "; a = " << *(pa.w_ptr() + i + deltaa) << std::endl;

}

static int32_t now()
{
    return  std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
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
    //std::cout << "Starting magic...\n";
    auto start = now();
    try
    {
        auto kernel = cl::KernelFunctor<const int, float, float, int, float, float, cl::Buffer&, cl::Buffer&, cl::Buffer&, cl::Buffer&, cl::Buffer&>(Kernels, "gradMagic");
        cl::Buffer bpgx(queue, pgx.r_ptr(),   pgx.end(),  true,  true);
        cl::Buffer bpgy(queue, pgy.r_ptr(),   pgy.end(),  true,  true);
        cl::Buffer bbx( queue, pbx.r_ptr(),   pbx.end(),  false, true);
        cl::Buffer bby( queue, pby.r_ptr(),   pby.end(),  false, true);
        cl::Buffer bres(queue, pres.r_ptr(),  pres.end(), false, true);
        //std::cout << "Ready to call kernel magic...\n";
        kernel(cl::EnqueueArgs(queue, cl::NDRange(gpuUsed), cl::NDRange(gpuUsed)), pgx.sizeAligned(), gpu16, gpu1, (is_deeper_magic) ? 1 : 0, alpha_s, fore_th, bpgx, bpgy, bbx, bby, bres).wait();
        //std::cout << "Call kernel magic ended...\n";
        cl::copy(bbx,  pbx.w_ptr(),  pbx.end());
        cl::copy(bby,  pby.w_ptr(),  pby.end());
        cl::copy(bres, pres.w_ptr(), pres.end());
        //std::cout << "Copied data to sysmemory...\n";
    }
    CATCHCL

    pbx.updateMatrixIfNeeded();
    pby.updateMatrixIfNeeded();
    pres.updateMatrixIfNeeded();
#ifndef NO_FPS
    std::cout << "Magic is done in (ms): " << now() - start << std::endl;
#endif
}

void openCl::sobel2(cv::Mat &gray, cv::Mat &float_out)
{
    static MatProxy<uchar> pgray(1);//don't align, will run "rectangular" kernel
    pgray.assign(gray, 0);

    static MatProxy<float> pout(1);
    pout.assign(float_out, gray.rows, gray.cols);


}
