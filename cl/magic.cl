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