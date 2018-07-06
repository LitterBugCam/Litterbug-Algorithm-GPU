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

//warning! I assume incoming memory is aligned to 16 * 12 !!! (12 cpus, 16 numbers per iteration in loop)
cl::Program getCompiledKernels()
{
    const static std::vector<std::string> source =
    {
        R"CLC(
        __kernel void cartToAngle(const int total, __global const float* gradx, __global const float* grady, __global float* radians)
        {
            private const size_t i = get_global_id(0);
            private const size_t elements_count = total / (12 * 16);
            private const size_t offset = i * total / 12;
            for (size_t k = 0; k < elements_count; ++k)
            {
               private float16 x = vload16( k , gradx + offset);
               private float16 y = vload16( k , grady + offset);
               vstore16(atan2(y, x) + 3.14159265f, k, radians + offset);
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
    Kernels = getCompiledKernels();
}

void openCl::atan2(cv::Mat &x, cv::Mat &y, cv::Mat &angle)
{
    const auto xs = x.rows * x.cols;
    const auto ys = y.rows * y.cols;
    assert(xs == ys);
    MatProxy<float> px(x, 1);
    MatProxy<float> py(y, 1);
    MatProxy<float> pa(angle, x.rows, x.cols);

    try
    {
        auto kernel = cl::KernelFunctor<const int32_t, cl::Buffer&, cl::Buffer&, cl::Buffer&>(Kernels, "cartToAngle");
        cl::Buffer bx(px.ptr(), px.end(), true);
        cl::Buffer by(py.ptr(), py.end(), true);
        cl::Buffer ba(pa.ptr(), pa.end(), false);
        //https://jorudolph.wordpress.com/2012/02/03/opencl-work-item-ids-globalgrouplocal/
        kernel(cl::EnqueueArgs(queue, cl::NDRange(12), cl::NDRange(1)), static_cast<int32_t>(xs), bx, by, ba).wait();
        cl::copy(ba, pa.ptr(), pa.end());
    }
    CATCHCL
    pa.updateMatrixIfNeeded();

}
