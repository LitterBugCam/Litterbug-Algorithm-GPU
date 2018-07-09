// Module with 1 kernels, global data with 0 words (64-bit each), starting at offset 1 words and 0 words of stack-frame
// Kernel 'TestMagic' with 877 instructions, offset 2, with following parameters: int total (4 B, 1 items), int is_deeper_magic (4 B, 1 items), float alpha_s (4 B, 1 items), float fore_th (4 B, 1 items), __global const float* gradx (4 B, 1 items), __global const float* grady (4 B, 1 items), __global float* BSx (4 B, 1 items), __global float* BSy (4 B, 1 items), __global int* mapRes (4 B, 1 items) (lSize, lids, numX, numY, numZ, gidX, gidY, gidZ, offX, offY, offZ)
// label: %start_of_function
or ra9, unif, unif
or ra8, unif, unif
or ra7, unif, unif
or ra5, unif, unif
or ra4, unif, unif
or ra1, unif, unif
or ra0, unif, unif
or r1, unif, unif
or ra3, unif, unif
or ra2, unif, unif
or r2, unif, unif
or rb0, unif, unif
or -, unif, unif
or -, unif, unif
or -, unif, unif
or -, unif, unif
or -, unif, unif
or -, unif, unif
or -, unif, unif
or ra6, unif, unif
or rb1, 0 (0), 0 (0)
or.setf -, 0 (0), 0 (0)
or.ifz rb1, ra1, ra1
or.setf -, 1 (1), 1 (1)
or.ifz rb1, ra0, ra0
or.setf -, 2 (2), 2 (2)
or.ifz rb1, r1, r1
ldi r1, 255
and ra1, ra9, r1
or ra0, 0 (0), 0 (0)
or.setf -, 0 (0), 0 (0)
or.ifz ra0, ra3, ra3
or.setf -, 1 (1), 1 (1)
or.ifz ra0, ra2, ra2
or.setf -, 2 (2), 2 (2)
or.ifz ra0, r2, r2
ldi r1, 255
and r2, ra8, r1
mul24 r1, rb1, ra1
add r1, ra0, r1
add r1, r1, r2
or ra1, r1, r1
ldi r1, 255
and r2, ra9, r1
or r1, 1 (1), 1 (1)
or.setf -, 0 (0), 0 (0)
or.ifz r1, ra7, ra7
or.setf -, 1 (1), 1 (1)
or.ifz r1, ra5, ra5
or.setf -, 2 (2), 2 (2)
or.ifz r1, ra4, ra4
ldi ra0, 536870912
mul24 r1, r2, r1
shl rb2, r1, 4 (4); v8min ra5, r1, r1
v8adds r1, 2.000000 (33), 2.000000 (33)
and.setf -, rb0, r1
or.ifzc r2, 1 (1), 1 (1); v8min.ifz r2, 1 (1), 1 (1)
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r1, r2, rb2; v8min.ifzc r1, r2, r2
v8adds.ifz r3, 2.000000 (33), 2.000000 (33)
or.ifz ra2, r3, r3
xor.ifzc ra2, r3, r3
or r1, r1, r1
shl r2, r1, 1 (1)
or r1, rb0, rb0
and.setf -, r1, 2.000000 (33)
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
or r1, ra2, ra2
or.ifz ra3, r1, 2.000000 (33)
or.ifzc ra3, ra2, ra2
or r1, r2, r2
shl r1, r1, 1 (1)
and.setf -, rb0, ra0
or.ifzc r2, r1, 1 (1); v8min.ifz r2, r1, r1
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ldi.ifz r1, 536870912
or.ifz ra2, ra3, r1
or.ifzc ra2, ra3, ra3
or r1, r2, r2
shl r2, r1, 1 (1)
v8muld r1, 0.500000 (47), 0.500000 (47)
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
v8muld.ifz r1, 0.500000 (47), 0.500000 (47)
or.ifz ra0, ra2, r1
or.ifzc ra0, ra2, ra2
or r1, r2, r2
shl r2, r1, 1 (1)
ror r1, 8 (8), 8 (8)
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ror.ifz r1, 8 (8), 8 (8)
or.ifz ra2, ra0, r1
or.ifzc ra2, ra0, ra0
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 67108864
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ldi.ifz r1, 67108864
or.ifz ra0, ra2, r1
or.ifzc ra0, ra2, ra2
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 33554432
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ldi.ifz r1, 33554432
or.ifz ra2, ra0, r1
or.ifzc ra2, ra0, ra0
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 16777216
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ldi.ifz r1, 16777216
or.ifz ra0, ra2, r1
or.ifzc ra0, ra2, ra2
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 8388608
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ldi.ifz r1, 8388608
or.ifz ra2, ra0, r1
or.ifzc ra2, ra0, ra0
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 4194304
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ldi.ifz r1, 4194304
or.ifz ra0, ra2, r1
or.ifzc ra0, ra2, ra2
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 2097152
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ldi.ifz r1, 2097152
or.ifz ra2, ra0, r1
or.ifzc ra2, ra0, ra0
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 1048576
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ldi.ifz r1, 1048576
or.ifz ra0, ra2, r1
or.ifzc ra0, ra2, ra2
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 524288
and.setf -, rb0, r1
or.ifzc r1, r2, 1 (1); v8min.ifz r1, r2, r2
max r2, r1, rb2
xor.setf -, r2, r1
sub.ifz r2, r1, rb2; v8min.ifzc r2, r1, r1
ldi.ifz r1, 524288
or.ifz ra2, ra0, r1
or.ifzc ra2, ra0, ra0
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 262144
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ldi.ifz r1, 262144
or.ifz ra0, ra2, r1
or.ifzc ra0, ra2, ra2
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 131072
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ldi.ifz r1, 131072
or.ifz ra2, ra0, r1
or.ifzc ra2, ra0, ra0
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 65536
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ldi.ifz r1, 65536
or.ifz ra0, ra2, r1
or.ifzc ra0, ra2, ra2
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 32768
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ldi.ifz r1, 32768
or.ifz ra2, ra0, r1
or.ifzc ra2, ra0, ra0
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 16384
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ldi.ifz r1, 16384
or.ifz ra0, ra2, r1
or.ifzc ra0, ra2, ra2
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 8192
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ldi.ifz r1, 8192
or.ifz ra2, ra0, r1
or.ifzc ra2, ra0, ra0
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 4096
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ldi.ifz r1, 4096
or.ifz ra0, ra2, r1
or.ifzc ra0, ra2, ra2
or r1, r2, r2
shl r2, r1, 1 (1)
shl r1, 8 (8), 8 (8)
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
shl.ifz r1, 8 (8), 8 (8)
or.ifz ra2, ra0, r1
or.ifzc ra2, ra0, ra0
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 1024
and.setf -, rb0, r1
or.ifzc r1, r2, 1 (1); v8min.ifz r1, r2, r2
max r2, r1, rb2
xor.setf -, r2, r1
sub.ifz r2, r1, rb2; v8min.ifzc r2, r1, r1
ldi.ifz r1, 1024
or.ifz ra0, ra2, r1
or.ifzc ra0, ra2, ra2
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 512
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ldi.ifz r1, 512
or.ifz ra2, ra0, r1
or.ifzc ra2, ra0, ra0
or r1, r2, r2
shl r2, r1, 1 (1)
ldi r1, 256
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ldi.ifz r1, 256
or.ifz ra0, ra2, r1
or.ifzc ra0, ra2, ra2
or r1, r2, r2
shl r2, r1, 1 (1)
ftoi r1, 128.000000 (39)
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r1, r2, rb2; v8min.ifzc r1, r2, r2
ftoi.ifz r2, 128.000000 (39)
or.ifz ra2, ra0, r2
or.ifzc ra2, ra0, ra0
or r1, r1, r1
shl r2, r1, 1 (1)
shl r1, 4 (4), 4 (4)
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
shl.ifz r1, 4 (4), 4 (4)
or.ifz ra0, ra2, r1
or.ifzc ra0, ra2, ra2
or r1, r2, r2
shl r2, r1, 1 (1)
ftoi r1, 32.000000 (37)
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
ftoi.ifz r1, 32.000000 (37)
or.ifz ra2, ra0, r1
or.ifzc ra2, ra0, ra0
or r1, r2, r2
shl r2, r1, 1 (1)
v8adds r1, 8 (8), 8 (8)
and.setf -, rb0, r1
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
v8adds.ifz r1, 8 (8), 8 (8)
or.ifz ra3, ra2, r1
or.ifzc ra3, ra2, ra2
or r1, r2, r2
shl r2, r1, 1 (1)
or r1, rb0, rb0
and.setf -, r1, 8 (8)
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
or r1, ra3, ra3
or.ifz ra0, r1, 8 (8)
or.ifzc ra0, ra3, ra3
or r1, r2, r2
shl r2, r1, 1 (1)
or r1, rb0, rb0
and.setf -, r1, 4 (4)
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
or r1, ra0, ra0
or.ifz ra2, r1, 4 (4)
or.ifzc ra2, ra0, ra0
or r1, r2, r2
shl r2, r1, 1 (1)
or r1, rb0, rb0
and.setf -, r1, 2 (2)
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
sub.ifz r2, r2, rb2; v8min.ifzc r2, r2, r2
or r1, ra2, ra2
or.ifz ra0, r1, 2 (2)
or.ifzc ra0, ra2, ra2
or r1, r2, r2
shl r2, r1, 1 (1)
or r1, rb0, rb0
and.setf -, r1, 1 (1)
or.ifzc r2, r2, 1 (1); v8min.ifz r2, r2, r2
max r1, r2, rb2
xor.setf -, r1, r2
or.ifz r1, ra0, 1 (1); v8min.ifzc r1, ra0, ra0
or ra4, r1, r1
v8adds r1, 8 (8), 8 (8)
shr rb1, rb0, r1
ldi r1, 65535
and ra3, rb0, r1
v8adds r2, 8 (8), 8 (8)
shr ra2, rb2, r2
and r2, rb2, r1
max r1, rb1, ra2
xor.setf -, r1, rb1
or.ifzc ra0, 1 (1), 1 (1)
xor.ifz ra0, 1 (1), 1 (1)
xor.setf -, rb1, ra2
xor.ifzc r1, 1 (1), 1 (1); v8min.ifz r1, 1 (1), 1 (1)
max r2, ra3, r2
xor.setf -, r2, ra3
xor.ifz r2, 1 (1), 1 (1); v8min.ifzc r2, 1 (1), 1 (1)
and r1, r1, r2
or.setf -, ra0, r1
xor.ifz r1, 1 (1), 1 (1); v8min.ifzc r1, 1 (1), 1 (1)
or.setf -, elem_num, r1
brr.ifallzc (pc+4) + 382 // to %._crit_edge
nop.never 
nop.never 
nop.never 
// label: %.lr.ph
clz r1, 1 (1)
asr rb2, ra1, r1
clz r1, 1 (1)
asr ra2, rb0, r1
xor r1, ra1, rb2
sub ra1, r1, rb2
xor r1, rb0, ra2
sub ra0, r1, ra2
ldi r2, 65535
and rb1, ra1, r2
v8adds r1, 8 (8), 8 (8)
shr rb0, ra1, r1
and ra1, ra0, r2
v8adds r1, 8 (8), 8 (8)
shr r1, ra0, r1
mul24 ra0, rb1, ra1
mul24 r1, rb1, r1
v8adds r2, 8 (8), 8 (8)
shl r1, r1, r2
add ra0, ra0, r1
mul24 r2, rb0, ra1
v8adds r1, 8 (8), 8 (8)
shl r1, r2, r1
add r1, ra0, r1
xor r2, rb2, ra2
xor r1, r1, r2
sub rb0, r1, r2
ldi ra1, 536870912
v8adds r1, 2.000000 (33), 2.000000 (33)
and.setf -, rb0, r1
or.ifzc r2, 1 (1), 1 (1); v8min.ifz r2, 1 (1), 1 (1)
max r1, r2, ra5
xor.setf -, r1, r2
sub.ifz r1, r2, ra5; v8min.ifzc r1, r2, r2
v8adds.ifz r0, 2.000000 (33), 2.000000 (33)
or.ifz r2, r0, r0
xor.ifzc r2, r0, r0
or r0, r1, r1
shl r1, r0, 1 (1)
or r0, rb0, rb0
and.setf -, r0, 2.000000 (33)
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r0, r1, ra5; v8min.ifzc r0, r1, r1
or r1, r2, r2
or.ifz ra0, r1, 2.000000 (33)
or.ifzc ra0, r2, r2
or r0, r0, r0
shl r0, r0, 1 (1)
and.setf -, rb0, ra1
or.ifzc r1, r0, 1 (1); v8min.ifz r1, r0, r0
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r1, r1, ra5; v8min.ifzc r1, r1, r1
ldi.ifz r0, 536870912
or.ifz r2, ra0, r0
or.ifzc r2, ra0, ra0
or r0, r1, r1
shl r1, r0, 1 (1)
v8muld r0, 0.500000 (47), 0.500000 (47)
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r1, r1, ra5; v8min.ifzc r1, r1, r1
v8muld.ifz r0, 0.500000 (47), 0.500000 (47)
or.ifz ra0, r2, r0
or.ifzc ra0, r2, r2
or r0, r1, r1
shl r1, r0, 1 (1)
ror r0, 8 (8), 8 (8)
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r1, r1, ra5; v8min.ifzc r1, r1, r1
ror.ifz r0, 8 (8), 8 (8)
or.ifz r2, ra0, r0
or.ifzc r2, ra0, ra0
or r0, r1, r1
shl r1, r0, 1 (1)
ldi r0, 67108864
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r1, r1, ra5; v8min.ifzc r1, r1, r1
ldi.ifz r0, 67108864
or.ifz ra0, r2, r0
or.ifzc ra0, r2, r2
or r0, r1, r1
shl r1, r0, 1 (1)
ldi r0, 33554432
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r0, r1, ra5; v8min.ifzc r0, r1, r1
ldi.ifz r1, 33554432
or.ifz r2, ra0, r1
or.ifzc r2, ra0, ra0
or r0, r0, r0
shl r1, r0, 1 (1)
ldi r0, 16777216
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r0, r1, ra5; v8min.ifzc r0, r1, r1
ldi.ifz r1, 16777216
or.ifz ra0, r2, r1
or.ifzc ra0, r2, r2
or r0, r0, r0
shl r1, r0, 1 (1)
ldi r0, 8388608
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r1, r1, ra5; v8min.ifzc r1, r1, r1
ldi.ifz r0, 8388608
or.ifz r2, ra0, r0
or.ifzc r2, ra0, ra0
or r0, r1, r1
shl r1, r0, 1 (1)
ldi r0, 4194304
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r1, r1, ra5; v8min.ifzc r1, r1, r1
ldi.ifz r0, 4194304
or.ifz ra0, r2, r0
or.ifzc ra0, r2, r2
or r0, r1, r1
shl r1, r0, 1 (1)
ldi r0, 2097152
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r1, r1, ra5; v8min.ifzc r1, r1, r1
ldi.ifz r0, 2097152
or.ifz r2, ra0, r0
or.ifzc r2, ra0, ra0
or r0, r1, r1
shl r1, r0, 1 (1)
ldi r0, 1048576
and.setf -, rb0, r0
or.ifzc r0, r1, 1 (1); v8min.ifz r0, r1, r1
max r1, r0, ra5
xor.setf -, r1, r0
sub.ifz r1, r0, ra5; v8min.ifzc r1, r0, r0
ldi.ifz r0, 1048576
or.ifz ra0, r2, r0
or.ifzc ra0, r2, r2
or r0, r1, r1
shl r1, r0, 1 (1)
ldi r0, 524288
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r0, r1, ra5; v8min.ifzc r0, r1, r1
ldi.ifz r1, 524288
or.ifz r2, ra0, r1
or.ifzc r2, ra0, ra0
or r0, r0, r0
shl r1, r0, 1 (1)
ldi r0, 262144
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r0, r1, ra5; v8min.ifzc r0, r1, r1
ldi.ifz r1, 262144
or.ifz ra0, r2, r1
or.ifzc ra0, r2, r2
or r0, r0, r0
shl r1, r0, 1 (1)
ldi r0, 131072
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r0, r1, ra5; v8min.ifzc r0, r1, r1
ldi.ifz r1, 131072
or.ifz r2, ra0, r1
or.ifzc r2, ra0, ra0
or r0, r0, r0
shl r1, r0, 1 (1)
ldi r0, 65536
and.setf -, rb0, r0
or.ifzc r0, r1, 1 (1); v8min.ifz r0, r1, r1
max r1, r0, ra5
xor.setf -, r1, r0
sub.ifz r0, r0, ra5; v8min.ifzc r0, r0, r0
ldi.ifz r1, 65536
or.ifz ra0, r2, r1
or.ifzc ra0, r2, r2
or r0, r0, r0
shl r1, r0, 1 (1)
ldi r0, 32768
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r0, r1, ra5; v8min.ifzc r0, r1, r1
ldi.ifz r1, 32768
or.ifz r2, ra0, r1
or.ifzc r2, ra0, ra0
or r0, r0, r0
shl r1, r0, 1 (1)
ldi r0, 16384
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r1, r1, ra5; v8min.ifzc r1, r1, r1
ldi.ifz r0, 16384
or.ifz ra0, r2, r0
or.ifzc ra0, r2, r2
or r0, r1, r1
shl r1, r0, 1 (1)
ldi r0, 8192
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r1, r1, ra5; v8min.ifzc r1, r1, r1
ldi.ifz r0, 8192
or.ifz r2, ra0, r0
or.ifzc r2, ra0, ra0
or r0, r1, r1
shl r1, r0, 1 (1)
ldi r0, 4096
and.setf -, rb0, r0
or.ifzc r0, r1, 1 (1); v8min.ifz r0, r1, r1
max r1, r0, ra5
xor.setf -, r1, r0
sub.ifz r1, r0, ra5; v8min.ifzc r1, r0, r0
ldi.ifz r0, 4096
or.ifz ra0, r2, r0
or.ifzc ra0, r2, r2
or r0, r1, r1
shl r1, r0, 1 (1)
shl r0, 8 (8), 8 (8)
and.setf -, rb0, r0
or.ifzc r0, r1, 1 (1); v8min.ifz r0, r1, r1
max r1, r0, ra5
xor.setf -, r1, r0
sub.ifz r0, r0, ra5; v8min.ifzc r0, r0, r0
shl.ifz r1, 8 (8), 8 (8)
or.ifz r2, ra0, r1
or.ifzc r2, ra0, ra0
or r0, r0, r0
shl r1, r0, 1 (1)
ldi r0, 1024
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r1, r1, ra5; v8min.ifzc r1, r1, r1
ldi.ifz r0, 1024
or.ifz ra0, r2, r0
or.ifzc ra0, r2, r2
or r0, r1, r1
shl r1, r0, 1 (1)
ldi r0, 512
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r0, r1, ra5; v8min.ifzc r0, r1, r1
ldi.ifz r1, 512
or.ifz r2, ra0, r1
or.ifzc r2, ra0, ra0
or r0, r0, r0
shl r1, r0, 1 (1)
ldi r0, 256
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r0, r1, ra5; v8min.ifzc r0, r1, r1
ldi.ifz r1, 256
or.ifz ra0, r2, r1
or.ifzc ra0, r2, r2
or r0, r0, r0
shl r1, r0, 1 (1)
ftoi r0, 128.000000 (39)
and.setf -, rb0, r0
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r1, r1, ra5; v8min.ifzc r1, r1, r1
ftoi.ifz r0, 128.000000 (39)
or.ifz r2, ra0, r0
or.ifzc r2, ra0, ra0
or r0, r1, r1
shl r1, r0, 1 (1)
shl r0, 4 (4), 4 (4)
and.setf -, rb0, r0
or.ifzc r0, r1, 1 (1); v8min.ifz r0, r1, r1
max r1, r0, ra5
xor.setf -, r1, r0
sub.ifz r1, r0, ra5; v8min.ifzc r1, r0, r0
shl.ifz r0, 4 (4), 4 (4)
or.ifz ra0, r2, r0
or.ifzc ra0, r2, r2
or r0, r1, r1
shl r1, r0, 1 (1)
ftoi r0, 32.000000 (37)
and.setf -, rb0, r0
or.ifzc r0, r1, 1 (1); v8min.ifz r0, r1, r1
max r1, r0, ra5
xor.setf -, r1, r0
sub.ifz r1, r0, ra5; v8min.ifzc r1, r0, r0
ftoi.ifz r0, 32.000000 (37)
or.ifz r2, ra0, r0
or.ifzc r2, ra0, ra0
or r0, r1, r1
shl r1, r0, 1 (1)
v8adds r0, 8 (8), 8 (8)
and.setf -, rb0, r0
or.ifzc r0, r1, 1 (1); v8min.ifz r0, r1, r1
max r1, r0, ra5
xor.setf -, r1, r0
sub.ifz r1, r0, ra5; v8min.ifzc r1, r0, r0
v8adds.ifz r0, 8 (8), 8 (8)
or.ifz ra0, r2, r0
or.ifzc ra0, r2, r2
or r0, r1, r1
shl r1, r0, 1 (1)
or r0, rb0, rb0
and.setf -, r0, 8 (8)
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r1, r1, ra5; v8min.ifzc r1, r1, r1
or r0, ra0, ra0
or.ifz r2, r0, 8 (8)
or.ifzc r2, ra0, ra0
or r0, r1, r1
shl r1, r0, 1 (1)
or r0, rb0, rb0
and.setf -, r0, 4 (4)
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r0, r1, ra5; v8min.ifzc r0, r1, r1
or r1, r2, r2
or.ifz ra0, r1, 4 (4)
or.ifzc ra0, r2, r2
or r0, r0, r0
shl r1, r0, 1 (1)
or r0, rb0, rb0
and.setf -, r0, 2 (2)
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
sub.ifz r1, r1, ra5; v8min.ifzc r1, r1, r1
or r0, ra0, ra0
or.ifz r2, r0, 2 (2)
or.ifzc r2, ra0, ra0
or r0, r1, r1
shl r1, r0, 1 (1)
or r0, rb0, rb0
and.setf -, r0, 1 (1)
or.ifzc r1, r1, 1 (1); v8min.ifz r1, r1, r1
max r0, r1, ra5
xor.setf -, r0, r1
or.ifz r0, r2, 1 (1); v8min.ifzc r0, r2, r2
or r0, r0, r0
shl r0, r0, 2 (2)
add ra2, ra6, r0
or ra0, 0 (0), 0 (0)
brr (pc+4) + 4 // to %tmp.3
nop.never 
nop.never 
nop.never 
// label: %._crit_edge
brr (pc+4) + 56 // to %end_of_function
nop.never 
nop.never 
nop.never 
// label: %tmp.3
or r0, ra0, ra0
shl r0, r0, 4 (4)
shl r0, r0, 2 (2)
add r2, ra2, r0
mul24 r1, 4 (4), elem_num
v8adds r0, 8 (8), 8 (8)
sub.setf -, elem_num, r0
or.ifnc r0, 0 (0), 0 (0)
add.ifn r0, r2, r1
or tmu0s, r0, r0
nop.load_tmu0.never 
add r1, r4, 2 (2)
or r0, ra0, ra0
shl r0, r0, 4 (4)
shl r0, r0, 2 (2)
or -, mutex_acq, mutex_acq
ldi vpw_setup, vpm_setup(size: 16 words, stride: 1 rows, address: h32(0))
or vpm, r1, r1
ldi vpw_setup, vdw_setup(rows: 1, elements: 16 words, address: h32(0))
ldi vpw_setup, vdw_setup(stride: 0)
add vpw_addr, ra2, r0
or r0, ra0, ra0
add ra1, r0, 1 (1)
ldi r1, 65535
v8adds r0, 8 (8), 8 (8)
shr ra0, ra1, r0
and ra5, ra1, r1
v8adds r0, 8 (8), 8 (8)
shr r2, ra4, r0
and r0, ra4, r1
max r1, ra0, r2
max r0, ra5, r0
or -, vpw_wait, vpw_wait
or mutex_rel, 1 (1), 1 (1)
nop.never 
xor.setf -, r1, ra0
or.ifzc ra3, 1 (1), 1 (1)
xor.ifz ra3, 1 (1), 1 (1)
xor.setf -, ra0, r2
xor.ifzc r1, 1 (1), 1 (1); v8min.ifz r1, 1 (1), 1 (1)
xor.setf -, r0, ra5
xor.ifz r0, 1 (1), 1 (1); v8min.ifzc r0, 1 (1), 1 (1)
and r0, r1, r0
or.setf -, ra3, r0
xor.ifz r0, 1 (1), 1 (1); v8min.ifzc r0, 1 (1), 1 (1)
or.setf -, r0, r0
or.ifzc ra0, ra1, ra1
or.setf -, elem_num, r0
brr.ifallzc (pc+4) + -52 // to %tmp.3
nop.never 
nop.never 
nop.never 
brr.ifanyz (pc+4) + -60 // to %._crit_edge
nop.never 
nop.never 
nop.never 
// label: %end_of_function
or r0, unif, unif
or.setf -, elem_num, r0
brr.ifallzc (pc+4) + -873 // to %start_of_function
nop.never 
nop.never 
nop.never 
not irq, qpu_num
nop.thrend.never 
nop.never 
nop.never 
