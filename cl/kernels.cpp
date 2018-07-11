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

                                             float16 myselectf1(float afalse, float atrue, int condition)
                                             {
                                                 float cond = condition * condition;
                                                 float not_cond = 1.f - cond;
                                                 return atrue * cond + afalse * not_cond;
                                             }

                                             int16 myselecti16(int16 afalse, int16 atrue, int16 condition)
                                             {
                                                 //we have -1 = true in condition ...it should be so
                                                 int16 cond     = condition * condition;
                                                 int16 not_cond = 1 - cond;
                                                 return atrue * cond + afalse * not_cond;
                                             }

                                             int16 myselecti1(int afalse, int atrue, int condition)
                                             {
                                                 int16 cond     = condition * condition;
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
        //https://software.intel.com/en-us/videos/optimizing-simple-opencl-kernels-sobel-kernel-optimization

        R"CLC(
        #define INP_MEM __global const
        __kernel void SobelAndMagicDetector(const int is_minus1, const int is_plus2, const int is_first_run, const float alpha_s, const float fore_th,
                                            INP_MEM uchar16* restrict input, __global float16* restrict grad_dir,
                                            __global float16* restrict BSx,  __global float16* restrict BSy, __global uchar16* restrict mapRes
                                           )
        {
            uint dstXStride = get_global_size(0); //original width / 16
            uint dstIndex   = 16 * get_global_id(1) * dstXStride + get_global_id(0);
            uint srcXStride = dstXStride + 2;
            uint srcIndex   = 16 * get_global_id(1) * srcXStride + get_global_id(0) + 1;

            const float16 as = alpha_s;
            const float16 fth = fore_th;
            const float16 v19 = 19;
            const int16 zeros = 0;
            const int16 ones  = 1;
            const int16 twos  = 2;
            const int16 twos5 = 255;

            float   a = (( INP_MEM uchar*)(input + srcIndex))[-1];
            float16 b = convert_float16(vload16(0, ( INP_MEM uchar*)(input + srcIndex)));
            float   c = (( INP_MEM uchar*)(input + srcIndex))[16];
            srcIndex += srcXStride;

            float   d = (( INP_MEM uchar*)(input + srcIndex))[-1];
            float16 e = convert_float16(vload16(0, ( INP_MEM uchar*)(input + srcIndex)));
            float   f = (( INP_MEM uchar*)(input + srcIndex))[16];

            for (int k = 0; k < 16; ++k)
            {
            srcIndex += srcXStride;
            float   g = (( INP_MEM uchar*)(input + srcIndex))[-1];
            float16 h = convert_float16(vload16(0, (INP_MEM uchar*)(input + srcIndex)));
            float   i = (( INP_MEM uchar*)(input + srcIndex))[16];

            float16 Gx =  (float16)    (a, b.s0123, b.s456789ab, b.scde) -     (float16)(b.s123, b.s4567, b.s89abdcef, c) +
                        2.f * (float16)(d, e.s0123, e.s456789ab, e.scde) - 2.f * (float16)(e.s123, e.s4567, e.s89abdcef, f) +
                        (float16)    (g, h.s0123, h.s456789ab, h.scde) -     (float16)(h.s123, h.s4567, h.s89abdcef, i);

            float16 Gy =  (float16)(a, b.s0123, b.s456789ab, b.scde) + 2.f * b + (float16)(b.s123, b.s4567, b.s89abdcef, c) -
                        (float16)(g, h.s0123, h.s456789ab, h.scde) - 2.f * h - (float16)(h.s123, h.s4567, h.s89abdcef, i);

            float16 an = myatan2f16(Gy, Gx);
            an = myselectf16(an, an + 6.2831853f, isless(an, 0));
            vstore16(an, 0, ( __global float*)(grad_dir + dstIndex));

            a = d; b = e; c = f;
            d = g; e = h; f = i;

            float16 bx = myselectf16(vload16(0, ( __global float*)(BSx + dstIndex)), Gx, is_first_run);
            float16 by = myselectf16(vload16(0, ( __global float*)(BSy + dstIndex)), Gy, is_first_run);

            float16 D_Sx = Gx - bx;
            bx += D_Sx * as;
            vstore16(bx, 0, ( __global float*)(BSx + dstIndex));

            float16 D_Sy = Gy - by;
            by += D_Sy * as;
            vstore16(by, 0, ( __global float*)(BSy + dstIndex));

            int16 mr           = ((is_minus1 || is_plus2)) ? convert_int16(vload16(0, ( __global uchar*)(mapRes + dstIndex))) : 0;
            mr -= is_minus1;
            int16 c1 = isgreater(fabs(D_Sx), fth) && isgreater(fabs(Gx), v19);
            int16 c2 = isgreater(fabs(D_Sy), fth) && isgreater(fabs(Gy), v19);

            mr += myselecti16(zeros, ones, c2 || c1) * twos;
            c1 = mr < zeros;
            c2 = myselecti16(mr, zeros, c1);//overflow protection
            c1 = c2 > twos5;
            mr = is_plus2 * myselecti16(c2, twos5, c1); //overflow protection
            if (is_minus1 || is_plus2)
               vstore16(convert_uchar16(mr), 0, ( __global uchar*)(mapRes + dstIndex));
            dstIndex += dstXStride;
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

int32_t TimeMeasure::now()
{
    return  std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}


//#define VARS(NAME,TYPE) static MatProxy<TYPE> p##NAME(1); p##NAME.assign(NAME, gray.rows, gray.cols)
#define VARS(NAME,TYPE) static MatProxy<TYPE> p##NAME(NAME, gray.rows, gray.cols, 1);
#define COPYD2H(NAME) cl::copy(queue, b##NAME,  p##NAME.w_ptr(),  p##NAME.end());
#define COPYH2D(NAME) cl::copy(queue, p##NAME.r_ptr(),  p##NAME.end(), b##NAME);

//some usefull link about __local memory: https://stackoverflow.com/questions/38345046/local-memory-using-c-wrappers
void openCl::sobel2magic(bool is_minus1, bool is_plus2, bool is_first_run, const float alpha_s, const float fore_th, cv::Mat &gray, cv::Mat& angle, cv::Mat& mapR)
{

    VARS(angle, float);
    VARS(mapR,  uint8_t);

    static cv::Mat gray_buf(gray.rows + 2, gray.cols + 32, gray.depth());
    cv::copyMakeBorder(gray, gray_buf, 1, 1, 16, 16, cv::BORDER_REPLICATE);

    static MatProxy<uchar> pgray(1);//don't align, will run "rectangular" kernel
    pgray.assign(gray_buf, 0);



    static cv::Mat abx;
    static cv::Mat aby;
    static MatProxy<float> pbx(abx, gray.rows, gray.cols, 1);
    static MatProxy<float> pby(aby, gray.rows, gray.cols, 1);

    static cl::Buffer bgray (queue, pgray.w_ptr(),    pgray.end(),  true, false);
    static cl::Buffer bangle(queue, pangle.w_ptr(),   pangle.end(), false, false);
    static cl::Buffer bbx   (queue, pbx.w_ptr(),   pbx.end(),  false, false);
    static cl::Buffer bby   (queue, pby.w_ptr(),   pby.end(),  false, false);
    static cl::Buffer bmapR (queue, pmapR.w_ptr(),  pmapR.end(), false, false);


    static auto gpus = gpuUsed;
    //std::cout << "Gpus used for sobel: " << gpus << std::endl;
    //std::cout << ((size_t)pangle.w_ptr()) << "   " << ((size_t)pmapR.w_ptr()) << std::endl;
    try
    {
        auto kernel = cl::KernelFunctor<int, int, int, float, float, cl::Buffer&, cl::Buffer&, cl::Buffer&, cl::Buffer&, cl::Buffer&> (Kernels, "SobelAndMagicDetector");
        COPYH2D(gray);
        COPYH2D(mapR);


        while (true)
            try
            {
                kernel(cl::EnqueueArgs(queue, cl::NDRange(gray.cols / 16, gray.rows / 16), cl::NDRange(gpus)), (is_minus1) ? 1 : 0, (is_plus2) ? 1 : 0, (is_first_run) ? -1 : 0, alpha_s,
                       fore_th, bgray, bangle, bbx, bby, bmapR).wait();
                break;
            }
            catch (cl::Error& err)
            {
                if (err.err() == -54)
                {
                    --gpus;
                    continue;
                }
                throw err;
            }
        COPYD2H(angle);
        if (is_plus2 || is_minus1)
            COPYD2H(mapR);
    }
    CATCHCL
    pangle.updateMatrixIfNeeded();

    if (is_plus2 || is_minus1)
        pmapR.updateMatrixIfNeeded();

}
#undef VARS
#undef COPY
#undef COPYD2H
