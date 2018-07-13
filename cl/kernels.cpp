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
    //those functions are bugged or absent into current VC4C compiler (for r-pi), so need some custom implementation
    const static std::string support_funcs = R"CLC(
                                             float16 myselectf16(float16 afalse, float16 atrue, int16 condition)
                                             {
                                                 //we have -1 = true in condition ...it should be so
                                                 float16 cond = convert_float16(condition * condition);
                                                 float16 not_cond = convert_float16(1 - condition * condition);
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

                                             uchar16 myselectuc16(uchar16 afalse, uchar16 atrue, int16 condition)
                                             {
                                                 //we have -1 = true in condition ...it should be so
                                                 uchar16 one = 1;
                                                 uchar16 cond     = convert_uchar16(condition * condition);
                                                 uchar16 not_cond = one - cond;
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

                                               //t3 = (fabs(y) > fabs(x)) ? 1.570796327f - t3 : t3;
                                               t3 = myselectf16(t3, 1.570796327f - t3, isgreater(fabs(y), fabs(x)));
                                               //t3 = (x < 0) ?  3.141592654f - t3 : t3;
                                               t3 = myselectf16(t3, 3.141592654f - t3, isless(x, 0));
                                               //t3 = (y < 0) ? -t3 : t3;
                                               t3 = myselectf16(t3, - t3, isless(y, 0));
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
        //#define NORM /255.f
        //#define DENORM *255.f
        #define NORM
        #define DENORM
        //z1 z2 z3
        //z4 z5 z6
        //z7 z8 z9

        #define Z1 ((float16)(a, b.s0123, b.s456789ab, b.scde))
        #define Z2 (b)
        #define Z3 (float16) (b.s123, b.s4567, b.s89abcdef, c)
        #define Z4 ((float16)(d, e.s0123, e.s456789ab, e.scde))
        #define Z5 (e)
        #define Z6 (float16)(e.s123, e.s4567, e.s89abcdef, f)
        #define Z7 (float16)(g, h.s0123, h.s456789ab, h.scde)
        #define Z8 (h)
        #define Z9 (float16)(h.s123, h.s4567, h.s89abcdef, i)

        #define INIT_PADDED uint dstXStride = get_global_size(0); uint dstIndex = 16 * get_global_id(1) * dstXStride + get_global_id(0);uint srcXStride = dstXStride + 2;uint srcIndex = 16 * get_global_id(1) * srcXStride + get_global_id(0) + 1
        #define NEXT_ROW a = d; b = e; c = f; d = g; e = h; f = i

        #define INPUT (( INP_MEM uchar*)(input + srcIndex))
        __kernel void SobelAndMagicDetector(const int is_minus1, const int is_plus2, const int is_first_run, const float alpha_s, const float fore_th,
                                            INP_MEM uchar16* restrict input, __global float16* restrict grad_dir,
                                            __global float16* restrict BSx,  __global float16* restrict BSy, __global uchar16* restrict mapRes
                                            ,__global float16* restrict alignedGAngle, __global float16* restrict alignedGMod
                                           )
        {
            INIT_PADDED;
            const float16 as  = alpha_s;
            const float16 fth = fore_th NORM;
            const float16 v19 = 19 NORM;
            const int16 zeros = 0;
            const int16 ones  = 1;
            const int16 twos  = 2;
            const int16 twos5 = 255;

            float   a = INPUT[-1]NORM;
            float16 b = convert_float16(vload16(0, INPUT))NORM;
            float   c = INPUT[16]NORM;
            srcIndex += srcXStride;

            float   d = INPUT[-1]NORM;
            float16 e = convert_float16(vload16(0, INPUT))NORM;
            float   f = INPUT[16]NORM;

            for (int k = 0; k < 16; ++k)
            {
                uint dstAlignedIndex = srcIndex; //ok, I hope that is correct, i.e. middle of the matrix is index
                srcIndex += srcXStride;
                float   g = INPUT[-1]NORM;
                float16 h = convert_float16(vload16(0, INPUT))NORM;
                float   i = INPUT[16]NORM;

                float16 Gx = (Z7 + 2 * Z8 + Z9) - (Z1 + 2 * Z2 +Z3);
                float16 Gy = (Z3 + 2 * Z6 + Z9) - (Z1 + 2 * Z4 +Z7);
                float16 an  = myatan2f16(Gy, Gx);

                //prepairing stuff for Canny - result will be gradient with [0; pi) - we dont care if it poinst left or right there
                     //float16 mag = sqrt(Gx * Gx + Gy * Gy); //maybe not working on PI
                     float16 mag = fabs(Gx) + fabs(Gy); //default opencv Canny behaviour
                     //float16 rad = fmod(an + 3.14159265f, 3.14159265f);
                     float16 rad = myselectf16(an, an + 3.14159265f, isless(an, 0));
                     vstore16(rad, 0, ( __global float*)(alignedGAngle + dstAlignedIndex));
                     vstore16(mag, 0, ( __global float*)(alignedGMod + dstAlignedIndex));
                //done here, must know full matrix prior can do non-maximum supression etc.

                an = myselectf16(an, an + 6.2831853f, isless(an, 0));
                vstore16(an, 0, ( __global float*)(grad_dir + dstIndex));
                NEXT_ROW;


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
                int16 c1 = isgreater(fabs(D_Sx), fth ) && isgreater(fabs(Gx), v19 );
                int16 c2 = isgreater(fabs(D_Sy), fth ) && isgreater(fabs(Gy), v19 );

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
       #undef INPUT

        //that is not full Canny, it uses pre-processed values from prior SobelAndMagicDetector
        //expecting angle is specially prepared in [0;pi) so we lost left or right, top or bottom, but we don't care here
        #define INPUT (( INP_MEM float*)(alignedGMod + srcIndex))
       __kernel void non_maximum(INP_MEM float16* restrict alignedGAngle, INP_MEM float16* restrict alignedGMod, __global float16* N)
        {
              const float16 pi8 = 0.39269908125f; //pi/8 (half width of interval around gradient ray)
              const float16 pi4 = 0.7853981625f;
              const float16 pi34= 3.f * 0.7853981625f;
              const float16 pi2 = 1.570796325f;
              const float16 pi1 = 3.14159265f;

              INIT_PADDED;
              float   a = INPUT[-1];
              float16 b = vload16(0, INPUT);
              float   c = INPUT[16];
              srcIndex += srcXStride;

              float   d = INPUT[-1];
              float16 e = vload16(0, INPUT);
              float   f = INPUT[16];


              for (int k = 0; k < 16; ++k)
              {
                  uint dstPaddedIndex = srcIndex;
                  float16 angle = convert_float16(vload16(0, ( INP_MEM float*)(alignedGAngle + srcIndex)));
                  srcIndex += srcXStride;

                  float   g = INPUT[-1];
                  float16 h = vload16(0, INPUT);
                  float   i = INPUT[16];

        //z1 z2 z3
        //z4 z5 z6
        //z7 z8 z9
                  //now we have loaded all 9 points (3x3) and x16 of them
                  //need to figure gradient line and pick 2 of 8 around current
                  float16 p1 = 0;
                  float16 p2 = 0;
                  int16   atest = 0;


                  atest =  islessequal(fabs(angle - pi2), pi8); //90 not sure why, but this works better 90 = up/left
                  p1 = myselectf16(p1, Z4, atest);
                  p2 = myselectf16(p2, Z6, atest);

                  atest =  isless(pi34, angle); //135
                  p1 = myselectf16(p1, Z3, atest);
                  p2 = myselectf16(p2, Z7, atest);

                  atest =  islessequal(angle, pi8); //0
                  p1 = myselectf16(p1, Z2, atest);
                  p2 = myselectf16(p2, Z8, atest);

                  atest =  islessequal(fabs(angle - pi1), pi8); //0
                  p1 = myselectf16(p1, Z2, atest);
                  p2 = myselectf16(p2, Z8, atest);

                  atest =  isless(fabs(angle - pi4), pi8); //45
                  p1 = myselectf16(p1, Z1, atest);
                  p2 = myselectf16(p2, Z9, atest);

                  float16 n = myselectf16(0, Z5, isless(p2, Z5) && isless(p1, Z5));

                  //vstore16(Z5, 0, ( __global float*)(N + dstPaddedIndex));//DELETE IT, UNCOMMENT BELOW (it just copies magnitude from Sobel to output - for testing)
                  vstore16(n, 0, ( __global float*)(N + dstPaddedIndex));
                  NEXT_ROW;
              }
        };
        #undef INPUT


        //that will be 1 pass for speed
        #define INPUT   (( __global float*)(paddedN + srcIndex))
        __kernel void hysterisis(__global float16* restrict paddedN,  __global uchar16* result)
        {
             const float16 T1 = 40.f NORM;
             const float16 T2 = 3.f * T1 NORM;

             INIT_PADDED;
             float   a = INPUT[-1];
             float16 b = vload16(0, INPUT);
             float   c = INPUT[16];
             srcIndex += srcXStride;

             float   d = INPUT[-1];
             float16 e = vload16(0, INPUT);
             float   f = INPUT[16];
             int changes = 0;
        //z1 z2 z3
        //z4 z5 z6
        //z7 z8 z9
             for (int k = 0; k < 16; ++k)
             {
                 uint dstPaddedIndex = srcIndex;
                 srcIndex += srcXStride;

                 float   g = INPUT[-1];
                 float16 h = vload16(0, INPUT);
                 float   i = INPUT[16];

                 //If the pixel gradient is between the two thresholds, then it will be accepted only if it is connected to a pixel that is above the upper threshold.

                 int16 surrounding_greater =                  isgreaterequal(Z5, T2);//If a pixel gradient is higher than the upper threshold, the pixel is accepted as an edge
                 surrounding_greater = surrounding_greater || isgreaterequal(Z1, T2);
                 surrounding_greater = surrounding_greater || isgreaterequal(Z2, T2);
                 surrounding_greater = surrounding_greater || isgreaterequal(Z3, T2);
                 surrounding_greater = surrounding_greater || isgreaterequal(Z4, T2);
                 surrounding_greater = surrounding_greater || isgreaterequal(Z6, T2);
                 surrounding_greater = surrounding_greater || isgreaterequal(Z7, T2);
                 surrounding_greater = surrounding_greater || isgreaterequal(Z8, T2);
                 surrounding_greater = surrounding_greater || isgreaterequal(Z9, T2);

                 int16 PE = isgreaterequal(Z5, T1);
                 float16 nz5 = myselectf16(myselectf16(0, Z5, PE), T2 + 1,  surrounding_greater && PE);


                 uchar16 hys = myselectuc16(0, 255, isgreaterequal(nz5, T2));
                 //uchar16 hys = convert_uchar16(Z5 DENORM); //just copy output of prev kernel


                 vstore16(hys, 0, ( __global uchar*)(result + dstIndex));
                 NEXT_ROW;
                 dstIndex += dstXStride;
             }
        };
        #undef INPUT
        #undef OUTPUT

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
void openCl::sobel2magic(bool is_minus1, bool is_plus2, bool is_first_run, const float alpha_s, const float fore_th, cv::Mat &gray, cv::Mat& angle, cv::Mat& mapR, cv::Mat& canny)
{

    const auto elems_size       = gray.rows * gray.cols;
    const auto sobel_elems_size = (gray.rows + 2) * (gray.cols + 32);

    //GPU only buffers
    static cl::Buffer bbx (CL_MEM_READ_WRITE, elems_size * sizeof(float));
    static cl::Buffer bby (CL_MEM_READ_WRITE, elems_size * sizeof(float));
    static cl::Buffer bga (CL_MEM_READ_WRITE, sobel_elems_size * sizeof(float)); //temporary gradient vectors, aligned
    static cl::Buffer bgm (CL_MEM_READ_WRITE, sobel_elems_size * sizeof(float)); //temporary gradient magnitudes, aligned
    static cl::Buffer bN  (CL_MEM_READ_WRITE, sobel_elems_size * sizeof(float)); //temporary non-maximum supression

    VARS(angle, float);
    VARS(mapR,  uint8_t);
    VARS(canny, uint8_t);
    static cv::Mat gray_buf(gray.rows + 2, gray.cols + 32, gray.depth());
    cv::copyMakeBorder(gray, gray_buf, 1, 1, 16, 16, cv::BORDER_REPLICATE);

    static MatProxy<uchar> pgray(1);//don't align, will run "rectangular" kernel
    pgray.assign(gray_buf, 0);


    static cl::Buffer bgray (queue, pgray.w_ptr(),    pgray.end(),  true, false);
    static cl::Buffer bangle(queue, pangle.w_ptr(),   pangle.end(), false, false);
    static cl::Buffer bmapR (queue, pmapR.w_ptr(),    pmapR.end(), false, false);
    static cl::Buffer bcanny(queue, pcanny.w_ptr(),   pcanny.end(), false, false);

    static auto gpus = gpuUsed;
    //std::cout << "Gpus used for sobel: " << gpus << std::endl;
    //std::cout << ((size_t)pangle.w_ptr()) << "   " << ((size_t)pmapR.w_ptr()) << std::endl;
    try
    {
        auto kernel = cl::KernelFunctor<int, int, int, float, float,
             cl::Buffer&, cl::Buffer&, cl::Buffer&, cl::Buffer&, cl::Buffer&,
             cl::Buffer&, cl::Buffer&> (Kernels, "SobelAndMagicDetector");

        auto kernel_non_maximum = cl::KernelFunctor<cl::Buffer&, cl::Buffer&, cl::Buffer&> (Kernels, "non_maximum");
        auto kernel_hyst  = cl::KernelFunctor<cl::Buffer&, cl::Buffer&> (Kernels, "hysterisis");
        COPYH2D(gray);
        COPYH2D(mapR);
        COPYH2D(canny);
        for (const int kw = gray.cols / 16, kh = gray.rows / 16; true;)
            try
            {
                kernel(cl::EnqueueArgs(queue, cl::NDRange(kw, kh), cl::NDRange(gpus)), (is_minus1) ? 1 : 0, (is_plus2) ? 1 : 0, (is_first_run) ? -1 : 0, alpha_s,
                       fore_th, bgray, bangle, bbx, bby, bmapR, bga, bgm).wait();

                //Canny using precalculated values by prior kernel
                kernel_non_maximum(cl::EnqueueArgs(queue, cl::NDRange(kw, kh), cl::NDRange(gpus)), bga, bgm, bN).wait();
                kernel_hyst (cl::EnqueueArgs(queue, cl::NDRange(kw, kh), cl::NDRange(gpus)), bN, bcanny).wait();

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
        COPYD2H(canny);
        if (is_plus2 || is_minus1)
            COPYD2H(mapR);
    }
    CATCHCL
    pangle.updateMatrixIfNeeded();
    pcanny.updateMatrixIfNeeded();

    if (is_plus2 || is_minus1)
        pmapR.updateMatrixIfNeeded();

}
#undef VARS
#undef COPY
#undef COPYD2H
