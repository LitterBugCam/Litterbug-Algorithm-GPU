// Module with 1 kernels, global data with 0 words (64-bit each), starting at offset 1 words and 0 words of stack-frame
// Kernel 'gradMagic' with 1345 instructions, offset 2, with following parameters: int total (4 B, 1 items), int is_deeper_magic (4 B, 1 items), float alpha_s (4 B, 1 items), float fore_th (4 B, 1 items), __global const float* gradx (4 B, 1 items), __global const float* grady (4 B, 1 items), __global float* BSx (4 B, 1 items), __global float* BSy (4 B, 1 items), __global int* mapRes (4 B, 1 items) (lSize, lids, numX, numY, numZ, gidX, gidY, gidZ, offX, offY, offZ)
// label: %start_of_function
or ra17, unif, unif
or ra16, unif, unif
or ra15, unif, unif
or ra14, unif, unif
or ra10, unif, unif
or r3, unif, unif
or r2, unif, unif
or r1, unif, unif
or ra4, unif, unif
or ra3, unif, unif
or ra2, unif, unif
or rb2, unif, unif
or ra13, unif, unif
or ra11, unif, unif
or ra12, unif, unif
or ra8, unif, unif
or ra9, unif, unif
or ra7, unif, unif
or ra6, unif, unif
or ra5, unif, unif
// label: %tmp.0
or ra1, 0 (0), 0 (0)
// label: %call.%tmp.1
or ra0, 0 (0), 0 (0)
or r0, ra1, ra1
xor.setf -, r0, 0 (0)
or.ifz ra0, r3, r3
xor.setf -, r0, 1 (1)
or.ifz ra0, r2, r2
xor.setf -, r0, 2 (2)
or.ifz ra0, r1, r1
or r0, ra1, ra1
mul24 r0, r0, 8 (8)
shr r1, ra17, r0
ldi r0, 255
and r3, r1, r0
or r2, 0 (0), 0 (0)
or r0, ra1, ra1
xor.setf -, r0, 0 (0)
or.ifz r2, ra4, ra4
xor.setf -, r0, 1 (1)
or.ifz r2, ra3, ra3
xor.setf -, r0, 2 (2)
or.ifz r2, ra2, ra2
or r0, ra1, ra1
mul24 r0, r0, 8 (8)
shr r1, ra16, r0
ldi r0, 255
and r1, r1, r0
mul24 r0, ra0, r3
add r0, r2, r0
add r0, r0, r1
or ra0, r0, r0
// label: %call.after
or r3, 0 (0), 0 (0)
nop.never 
// label: %call1.%tmp.2
or r0, r3, r3
mul24 r0, r0, 8 (8)
shr r1, ra17, r0
ldi r0, 255
and r2, r1, r0
or r1, 1 (1), 1 (1)
or r0, r3, r3
xor.setf -, r0, 0 (0)
or.ifz r1, ra15, ra15
xor.setf -, r0, 1 (1)
or.ifz r1, ra14, ra14
xor.setf -, r0, 2 (2)
or.ifz r1, ra10, ra10
nop.never 
mul24 r0, r2, r1
or ra3, r0, r0
nop.never 
// label: %call1.after
or r0, ra3, ra3
shl ra2, r0, 4 (4)
or r0, 0 (0), 0 (0)
or ra1, 0 (0), 0 (0)
shl r2, r0, 1 (1)
v8adds r0, 2.000000 (33), 2.000000 (33)
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
v8adds.ifz r0, 2.000000 (33), 2.000000 (33)
or.ifz r3, ra1, r0
or.ifzc r3, ra1, ra1
shl r2, r2, 1 (1)
or r0, rb2, rb2
and.setf -, r0, 2.000000 (33)
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
or r0, r3, r3
or.ifz ra1, r0, 2.000000 (33)
or.ifzc ra1, r3, r3
shl r2, r2, 1 (1)
ldi r0, 536870912
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
ldi.ifz r0, 536870912
or.ifz r3, ra1, r0
or.ifzc r3, ra1, ra1
shl r2, r2, 1 (1)
v8muld r0, 0.500000 (47), 0.500000 (47)
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
v8muld.ifz r0, 0.500000 (47), 0.500000 (47)
or.ifz ra1, r3, r0
or.ifzc ra1, r3, r3
shl r2, r2, 1 (1)
ror r0, 8 (8), 8 (8)
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
ror.ifz r0, 8 (8), 8 (8)
or.ifz r3, ra1, r0
or.ifzc r3, ra1, ra1
shl r2, r2, 1 (1)
ldi r0, 67108864
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
ldi.ifz r0, 67108864
or.ifz ra1, r3, r0
or.ifzc ra1, r3, r3
shl r2, r2, 1 (1)
ldi r0, 33554432
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
ldi.ifz r0, 33554432
or.ifz r3, ra1, r0
or.ifzc r3, ra1, ra1
shl r2, r2, 1 (1)
ldi r0, 16777216
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
ldi.ifz r0, 16777216
or.ifz ra1, r3, r0
or.ifzc ra1, r3, r3
shl r2, r2, 1 (1)
ldi r0, 8388608
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r3, r1, ra2
or.ifzc r3, r1, r1
ldi.ifz r0, 8388608
or.ifz r2, ra1, r0
or.ifzc r2, ra1, ra1
shl r1, r3, 1 (1)
ldi r0, 4194304
and.setf -, rb2, r0
or.ifzc r0, r1, 1 (1)
or.ifz r0, r1, r1
max r1, r0, ra2
xor.setf -, r1, r0
sub.ifz r1, r0, ra2
or.ifzc r1, r0, r0
ldi.ifz r0, 4194304
or.ifz ra1, r2, r0
or.ifzc ra1, r2, r2
shl r2, r1, 1 (1)
ldi r0, 2097152
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
ldi.ifz r0, 2097152
or.ifz r3, ra1, r0
or.ifzc r3, ra1, ra1
shl r2, r2, 1 (1)
ldi r0, 1048576
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
ldi.ifz r0, 1048576
or.ifz ra1, r3, r0
or.ifzc ra1, r3, r3
shl r2, r2, 1 (1)
ldi r0, 524288
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r3, r1, ra2
or.ifzc r3, r1, r1
ldi.ifz r0, 524288
or.ifz r2, ra1, r0
or.ifzc r2, ra1, ra1
shl r1, r3, 1 (1)
ldi r0, 262144
and.setf -, rb2, r0
or.ifzc r0, r1, 1 (1)
or.ifz r0, r1, r1
max r1, r0, ra2
xor.setf -, r1, r0
sub.ifz r1, r0, ra2
or.ifzc r1, r0, r0
ldi.ifz r0, 262144
or.ifz ra1, r2, r0
or.ifzc ra1, r2, r2
shl r2, r1, 1 (1)
ldi r0, 131072
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
ldi.ifz r0, 131072
or.ifz r3, ra1, r0
or.ifzc r3, ra1, ra1
shl r2, r2, 1 (1)
ldi r0, 65536
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
ldi.ifz r0, 65536
or.ifz ra1, r3, r0
or.ifzc ra1, r3, r3
shl r2, r2, 1 (1)
ldi r0, 32768
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
ldi.ifz r0, 32768
or.ifz r3, ra1, r0
or.ifzc r3, ra1, ra1
shl r2, r2, 1 (1)
ldi r0, 16384
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
ldi.ifz r0, 16384
or.ifz ra1, r3, r0
or.ifzc ra1, r3, r3
shl r2, r2, 1 (1)
ldi r0, 8192
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
ldi.ifz r0, 8192
or.ifz r3, ra1, r0
or.ifzc r3, ra1, ra1
shl r2, r2, 1 (1)
ldi r0, 4096
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
ldi.ifz r0, 4096
or.ifz ra1, r3, r0
or.ifzc ra1, r3, r3
shl r2, r2, 1 (1)
shl r0, 8 (8), 8 (8)
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r3, r1, ra2
or.ifzc r3, r1, r1
shl.ifz r0, 8 (8), 8 (8)
or.ifz r2, ra1, r0
or.ifzc r2, ra1, ra1
shl r1, r3, 1 (1)
ldi r0, 1024
and.setf -, rb2, r0
or.ifzc r0, r1, 1 (1)
or.ifz r0, r1, r1
max r1, r0, ra2
xor.setf -, r1, r0
sub.ifz r1, r0, ra2
or.ifzc r1, r0, r0
ldi.ifz r0, 1024
or.ifz ra1, r2, r0
or.ifzc ra1, r2, r2
shl r2, r1, 1 (1)
ldi r0, 512
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
ldi.ifz r0, 512
or.ifz r3, ra1, r0
or.ifzc r3, ra1, ra1
shl r2, r2, 1 (1)
ldi r0, 256
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
ldi.ifz r0, 256
or.ifz ra1, r3, r0
or.ifzc ra1, r3, r3
shl r2, r2, 1 (1)
ftoi r0, 128.000000 (39)
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
ftoi.ifz r0, 128.000000 (39)
or.ifz r3, ra1, r0
or.ifzc r3, ra1, ra1
shl r2, r2, 1 (1)
shl r0, 4 (4), 4 (4)
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
shl.ifz r0, 4 (4), 4 (4)
or.ifz ra1, r3, r0
or.ifzc ra1, r3, r3
shl r2, r2, 1 (1)
ftoi r0, 32.000000 (37)
and.setf -, rb2, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r3, r1, ra2
or.ifzc r3, r1, r1
ftoi.ifz r0, 32.000000 (37)
or.ifz r2, ra1, r0
or.ifzc r2, ra1, ra1
shl r1, r3, 1 (1)
v8adds r0, 8 (8), 8 (8)
and.setf -, rb2, r0
or.ifzc r0, r1, 1 (1)
or.ifz r0, r1, r1
max r1, r0, ra2
xor.setf -, r1, r0
sub.ifz r1, r0, ra2
or.ifzc r1, r0, r0
v8adds.ifz r0, 8 (8), 8 (8)
or.ifz r3, r2, r0
or.ifzc r3, r2, r2
shl r2, r1, 1 (1)
or r0, rb2, rb2
and.setf -, r0, 8 (8)
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r2, r1, ra2
or.ifzc r2, r1, r1
or r0, r3, r3
or.ifz ra1, r0, 8 (8)
or.ifzc ra1, r3, r3
shl r2, r2, 1 (1)
or r0, rb2, rb2
and.setf -, r0, 4 (4)
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r3, r1, ra2
or.ifzc r3, r1, r1
or r0, ra1, ra1
or.ifz r2, r0, 4 (4)
or.ifzc r2, ra1, ra1
shl r1, r3, 1 (1)
or r0, rb2, rb2
and.setf -, r0, 2 (2)
or.ifzc r0, r1, 1 (1)
or.ifz r0, r1, r1
max r1, r0, ra2
xor.setf -, r1, r0
sub.ifz r1, r0, ra2
or.ifzc r1, r0, r0
or r0, r2, r2
or.ifz r3, r0, 2 (2)
or.ifzc r3, r2, r2
shl r2, r1, 1 (1)
or r0, rb2, rb2
and.setf -, r0, 1 (1)
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra2
xor.setf -, r0, r1
sub.ifz r0, r1, ra2
or.ifzc r0, r1, r1
or r0, r3, r3
or.ifz r0, r0, 1 (1)
or.ifzc r0, r3, r3
or ra10, r0, r0
clz r0, 1 (1)
asr rb0, ra0, r0
nop.never 
xor r0, ra0, rb0
sub r3, r0, rb0
clz r0, 1 (1)
asr ra1, rb2, r0
nop.never 
xor r0, rb2, ra1
sub r2, r0, ra1
ldi r0, 65535
and r1, r3, r0
v8adds r0, 8 (8), 8 (8)
shr ra0, r3, r0
ldi r0, 65535
and r3, r2, r0
v8adds r0, 8 (8), 8 (8)
shr r0, r2, r0
mul24 r2, r1, r3
mul24 r1, r1, r0
v8adds r0, 8 (8), 8 (8)
shl r1, r1, r0
nop.never 
add r2, r2, r1
mul24 r1, ra0, r3
v8adds r0, 8 (8), 8 (8)
shl r0, r1, r0
add r0, r2, r0
xor r1, rb0, ra1
xor r0, r0, r1
sub ra1, r0, r1
or r0, 0 (0), 0 (0)
or ra0, 0 (0), 0 (0)
shl r2, r0, 1 (1)
v8adds r0, 2.000000 (33), 2.000000 (33)
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
v8adds.ifz r0, 2.000000 (33), 2.000000 (33)
or.ifz r3, ra0, r0
or.ifzc r3, ra0, ra0
shl r2, r2, 1 (1)
or r0, ra1, ra1
and.setf -, r0, 2.000000 (33)
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
or r0, r3, r3
or.ifz ra4, r0, 2.000000 (33)
or.ifzc ra4, r3, r3
shl r2, r2, 1 (1)
ldi r0, 536870912
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 536870912
or.ifz ra0, ra4, r0
or.ifzc ra0, ra4, ra4
shl r2, r2, 1 (1)
v8muld r0, 0.500000 (47), 0.500000 (47)
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r3, r1, ra3
or.ifzc r3, r1, r1
v8muld.ifz r0, 0.500000 (47), 0.500000 (47)
or.ifz r2, ra0, r0
or.ifzc r2, ra0, ra0
shl r1, r3, 1 (1)
ror r0, 8 (8), 8 (8)
and.setf -, ra1, r0
or.ifzc r0, r1, 1 (1)
or.ifz r0, r1, r1
max r1, r0, ra3
xor.setf -, r1, r0
sub.ifz r1, r0, ra3
or.ifzc r1, r0, r0
ror.ifz r0, 8 (8), 8 (8)
or.ifz r3, r2, r0
or.ifzc r3, r2, r2
shl r2, r1, 1 (1)
ldi r0, 67108864
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 67108864
or.ifz ra0, r3, r0
or.ifzc ra0, r3, r3
shl r2, r2, 1 (1)
ldi r0, 33554432
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 33554432
or.ifz r3, ra0, r0
or.ifzc r3, ra0, ra0
shl r2, r2, 1 (1)
ldi r0, 16777216
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 16777216
or.ifz ra0, r3, r0
or.ifzc ra0, r3, r3
shl r2, r2, 1 (1)
ldi r0, 8388608
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 8388608
or.ifz r3, ra0, r0
or.ifzc r3, ra0, ra0
shl r2, r2, 1 (1)
ldi r0, 4194304
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 4194304
or.ifz ra0, r3, r0
or.ifzc ra0, r3, r3
shl r2, r2, 1 (1)
ldi r0, 2097152
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 2097152
or.ifz r3, ra0, r0
or.ifzc r3, ra0, ra0
shl r2, r2, 1 (1)
ldi r0, 1048576
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 1048576
or.ifz ra0, r3, r0
or.ifzc ra0, r3, r3
shl r2, r2, 1 (1)
ldi r0, 524288
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 524288
or.ifz r3, ra0, r0
or.ifzc r3, ra0, ra0
shl r2, r2, 1 (1)
ldi r0, 262144
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 262144
or.ifz ra0, r3, r0
or.ifzc ra0, r3, r3
shl r2, r2, 1 (1)
ldi r0, 131072
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 131072
or.ifz r3, ra0, r0
or.ifzc r3, ra0, ra0
shl r2, r2, 1 (1)
ldi r0, 65536
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 65536
or.ifz ra0, r3, r0
or.ifzc ra0, r3, r3
shl r2, r2, 1 (1)
ldi r0, 32768
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 32768
or.ifz r3, ra0, r0
or.ifzc r3, ra0, ra0
shl r2, r2, 1 (1)
ldi r0, 16384
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 16384
or.ifz ra0, r3, r0
or.ifzc ra0, r3, r3
shl r2, r2, 1 (1)
ldi r0, 8192
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 8192
or.ifz r3, ra0, r0
or.ifzc r3, ra0, ra0
shl r2, r2, 1 (1)
ldi r0, 4096
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 4096
or.ifz ra0, r3, r0
or.ifzc ra0, r3, r3
shl r2, r2, 1 (1)
shl r0, 8 (8), 8 (8)
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
shl.ifz r0, 8 (8), 8 (8)
or.ifz r3, ra0, r0
or.ifzc r3, ra0, ra0
shl r2, r2, 1 (1)
ldi r0, 1024
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 1024
or.ifz ra0, r3, r0
or.ifzc ra0, r3, r3
shl r2, r2, 1 (1)
ldi r0, 512
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 512
or.ifz r3, ra0, r0
or.ifzc r3, ra0, ra0
shl r2, r2, 1 (1)
ldi r0, 256
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ldi.ifz r0, 256
or.ifz ra0, r3, r0
or.ifzc ra0, r3, r3
shl r2, r2, 1 (1)
ftoi r0, 128.000000 (39)
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ftoi.ifz r0, 128.000000 (39)
or.ifz r3, ra0, r0
or.ifzc r3, ra0, ra0
shl r2, r2, 1 (1)
shl r0, 4 (4), 4 (4)
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
shl.ifz r0, 4 (4), 4 (4)
or.ifz ra0, r3, r0
or.ifzc ra0, r3, r3
shl r2, r2, 1 (1)
ftoi r0, 32.000000 (37)
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
ftoi.ifz r0, 32.000000 (37)
or.ifz r3, ra0, r0
or.ifzc r3, ra0, ra0
shl r2, r2, 1 (1)
v8adds r0, 8 (8), 8 (8)
and.setf -, ra1, r0
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
v8adds.ifz r0, 8 (8), 8 (8)
or.ifz ra0, r3, r0
or.ifzc ra0, r3, r3
shl r2, r2, 1 (1)
or r0, ra1, ra1
and.setf -, r0, 8 (8)
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
or r0, ra0, ra0
or.ifz r3, r0, 8 (8)
or.ifzc r3, ra0, ra0
shl r2, r2, 1 (1)
or r0, ra1, ra1
and.setf -, r0, 4 (4)
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r2, r1, ra3
or.ifzc r2, r1, r1
or r0, r3, r3
or.ifz ra0, r0, 4 (4)
or.ifzc ra0, r3, r3
shl r2, r2, 1 (1)
or r0, ra1, ra1
and.setf -, r0, 2 (2)
or.ifzc r1, r2, 1 (1)
or.ifz r1, r2, r2
max r0, r1, ra3
xor.setf -, r0, r1
sub.ifz r3, r1, ra3
or.ifzc r3, r1, r1
or r0, ra0, ra0
or.ifz r2, r0, 2 (2)
or.ifzc r2, ra0, ra0
shl r1, r3, 1 (1)
or r0, ra1, ra1
and.setf -, r0, 1 (1)
or.ifzc r0, r1, 1 (1)
or.ifz r0, r1, r1
max r1, r0, ra3
xor.setf -, r1, r0
sub.ifz r0, r0, ra3
or.ifzc r0, r0, r0
or r0, r2, r2
or.ifz r0, r0, 1 (1)
or.ifzc r0, r2, r2
or ra0, r0, r0
or r1, ra13, ra13
xor.setf -, elem_num, 0 (0)
or.ifz r0, r1, r1
nop.never 
or rep_all, r0, r0
or rb1, r5, r5
v8adds r0, 8 (8), 8 (8)
shr r3, rb2, r0
ldi r0, 65535
and r2, rb2, r0
v8adds r0, 8 (8), 8 (8)
shr ra1, ra2, r0
ldi r0, 65535
and ra2, ra2, r0
max r0, r3, ra1
xor.setf -, r0, r3
or.ifzc r1, 1 (1), 1 (1)
xor.ifz r1, 1 (1), 1 (1)
xor.setf -, r3, ra1
or.ifz r3, 1 (1), 1 (1)
xor.ifzc r3, 1 (1), 1 (1)
max r0, r2, ra2
xor.setf -, r0, r2
or.ifzc r0, 1 (1), 1 (1)
xor.ifz r0, 1 (1), 1 (1)
and r0, r3, r0
or.setf -, r1, r0
or.ifzc r0, 1 (1), 1 (1)
xor.ifz r0, 1 (1), 1 (1)
or.setf -, elem_num, r0
brr.ifallzc (pc+4) + 33 // to %._crit_edge
nop.never 
nop.never 
nop.never 
brr.ifanyz (pc+4) + 0 // to %.lr.ph
nop.never 
nop.never 
nop.never 
// label: %.lr.ph
or r0, ra11, ra11
xor.setf -, elem_num, 0 (0)
or.ifz r1, r0, r0
nop.never 
or rep_all, r1, r1
or rb2, r5, r5
or r1, ra0, ra0
shl r0, r1, 2 (2)
add ra8, ra8, r0
shl r0, r1, 2 (2)
add ra4, ra7, r0
shl r0, r1, 2 (2)
add ra11, ra9, r0
or r0, ra0, ra0
shl r1, r0, 2 (2)
add ra3, ra6, r1
shl r0, r0, 2 (2)
add ra5, ra5, r0
or r1, ra12, ra12
xor.setf -, elem_num, 0 (0)
or.ifz r0, r1, r1
nop.never 
or rep_all, r0, r0
or ra9, r5, r5
or ra6, 0 (0), 0 (0)
brr (pc+4) + 4 // to %tmp.3
nop.never 
nop.never 
nop.never 
// label: %._crit_edge
brr (pc+4) + 387 // to %end_of_function
nop.never 
nop.never 
nop.never 
// label: %tmp.3
or r0, ra6, ra6
or r1, ra8, ra8
// label: %call6.%tmp.4
or r0, r0, r0
shl r0, r0, 4 (4)
shl r0, r0, 2 (2)
add r0, r1, r0
or r1, r0, r0
mul24 r2, 4 (4), elem_num
v8adds r0, 8 (8), 8 (8)
sub.setf -, elem_num, r0
or.ifnc r0, 0 (0), 0 (0)
add.ifn r0, r1, r2
or tmu0s, r0, r0
nop.load_tmu0.never 
or r0, r4, r4
or ra2, r0, r0
// label: %call6.after
or r0, ra6, ra6
or r1, ra4, ra4
// label: %call8.%tmp.4
or r0, r0, r0
shl r0, r0, 4 (4)
shl r0, r0, 2 (2)
add r0, r1, r0
or r1, r0, r0
mul24 r2, 4 (4), elem_num
v8adds r0, 8 (8), 8 (8)
sub.setf -, elem_num, r0
or.ifnc r0, 0 (0), 0 (0)
add.ifn r0, r1, r2
or tmu0s, r0, r0
nop.load_tmu0.never 
or r0, r4, r4
or r1, r0, r0
nop.never 
// label: %call8.after
fsub r3, ra2, r1
nop.never 
fmul r0, rb2, r3
fadd r0, r1, r0
or r2, r0, r0
or r0, ra6, ra6
or r1, ra4, ra4
// label: %_Z8vstore16fjPU3AS1f.1804289383.%tmp.7
or r0, r0, r0
shl r0, r0, 4 (4)
shl r0, r0, 2 (2)
add r0, r1, r0
or r0, r0, r0
or -, mutex_acq, mutex_acq
ldi vpw_setup, vpm_setup(size: 16 words, stride: 1 rows, address: h32(0))
or vpm, r2, r2
ldi vpw_setup, vdw_setup(rows: 1, elements: 16 words, address: h32(0))
ldi vpw_setup, vdw_setup(stride: 0)
or vpw_addr, r0, r0
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
or -, vpw_wait, vpw_wait
or mutex_rel, 1 (1), 1 (1)
// label: %_Z8vstore16fjPU3AS1f.1804289383.after
or r0, ra6, ra6
or r1, ra11, ra11
// label: %call12.%tmp.4
or r0, r0, r0
shl r0, r0, 4 (4)
shl r0, r0, 2 (2)
add r0, r1, r0
or r2, r0, r0
mul24 r1, 4 (4), elem_num
v8adds r0, 8 (8), 8 (8)
sub.setf -, elem_num, r0
or.ifnc r0, 0 (0), 0 (0)
add.ifn r0, r2, r1
or tmu0s, r0, r0
nop.load_tmu0.never 
or r0, r4, r4
or ra7, r0, r0
// label: %call12.after
or r0, ra6, ra6
or r1, ra3, ra3
// label: %call14.%tmp.4
or r0, r0, r0
shl r0, r0, 4 (4)
shl r0, r0, 2 (2)
add r0, r1, r0
or r2, r0, r0
mul24 r1, 4 (4), elem_num
v8adds r0, 8 (8), 8 (8)
sub.setf -, elem_num, r0
or.ifnc r0, 0 (0), 0 (0)
add.ifn r0, r2, r1
or tmu0s, r0, r0
nop.load_tmu0.never 
or r0, r4, r4
or r1, r0, r0
nop.never 
// label: %call14.after
fsub ra0, ra7, r1
nop.never 
fmul r0, rb2, ra0
fadd r0, r1, r0
or r2, r0, r0
or r0, ra6, ra6
or r1, ra3, ra3
// label: %_Z8vstore16fjPU3AS1f.846930886.%tmp.7
or r0, r0, r0
shl r0, r0, 4 (4)
shl r0, r0, 2 (2)
add r0, r1, r0
or r0, r0, r0
or -, mutex_acq, mutex_acq
ldi vpw_setup, vpm_setup(size: 16 words, stride: 1 rows, address: h32(0))
or vpm, r2, r2
ldi vpw_setup, vdw_setup(rows: 1, elements: 16 words, address: h32(0))
ldi vpw_setup, vdw_setup(stride: 0)
or vpw_addr, r0, r0
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
or -, vpw_wait, vpw_wait
or mutex_rel, 1 (1), 1 (1)
// label: %_Z8vstore16fjPU3AS1f.846930886.after
or r0, ra6, ra6
or r1, ra5, ra5
// label: %call20.%tmp.11
or r0, r0, r0
shl r0, r0, 4 (4)
shl r0, r0, 2 (2)
add r0, r1, r0
or r1, r0, r0
mul24 r2, 4 (4), elem_num
v8adds r0, 8 (8), 8 (8)
sub.setf -, elem_num, r0
or.ifnc r0, 0 (0), 0 (0)
add.ifn r0, r1, r2
or tmu0s, r0, r0
nop.load_tmu0.never 
or r0, r4, r4
or r0, r0, r0
nop.never 
// label: %call20.after
sub ra1, r0, rb1
or r0, r3, r3
nop.never 
// label: %call24.%tmp.14
or r0, r0, r0
fmaxabs r0, r0, 0 (0)
or r0, r0, r0
nop.never 
// label: %call24.after
or r1, r0, r0
or r0, ra9, ra9
nop.never 
// label: %call25.%tmp.15
fsub.setf -, r0, r1
or.ifn r1, 1 (1), 1 (1)
xor.ifnc r1, 1 (1), 1 (1)
or r0, -1 (31), -1 (31)
or r0, r0, r0
xor.setf -, elem_num, 0 (0)
or.ifz r2, r0, r0
nop.never 
or rep_all, r2, r2
or r0, r5, r5
or.setf -, r1, r1
or.ifzc r0, r0, r0
or.ifz r0, 0 (0), 0 (0)
or r3, r0, r0
// label: %call25.after
or r0, ra2, ra2
nop.never 
// label: %call26.%tmp.14
or r0, r0, r0
fmaxabs r0, r0, 0 (0)
or r0, r0, r0
nop.never 
// label: %call26.after
or r1, r0, r0
ldi r0, 1100480512
nop.never 
// label: %call27.%tmp.15
fsub.setf -, r0, r1
or.ifn r2, 1 (1), 1 (1)
xor.ifnc r2, 1 (1), 1 (1)
or r1, -1 (31), -1 (31)
or r1, r1, r1
xor.setf -, elem_num, 0 (0)
or.ifz r0, r1, r1
nop.never 
or rep_all, r0, r0
or r0, r5, r5
or.setf -, r2, r2
or.ifzc r0, r0, r0
or.ifz r0, 0 (0), 0 (0)
or r1, r0, r0
// label: %call27.after
or r0, r3, r3
xor.setf -, r0, 0 (0)
or.ifzc r2, 1 (1), 1 (1)
xor.ifz r2, 1 (1), 1 (1)
or r0, r1, r1
xor.setf -, r0, 0 (0)
or.ifzc r0, 1 (1), 1 (1)
xor.ifz r0, 1 (1), 1 (1)
and ra2, r0, r2
or r0, ra0, ra0
nop.never 
// label: %call30.%tmp.14
or r0, r0, r0
fmaxabs r0, r0, 0 (0)
or r0, r0, r0
nop.never 
// label: %call30.after
or r1, r0, r0
or r0, ra9, ra9
nop.never 
// label: %call31.%tmp.15
fsub.setf -, r0, r1
or.ifn r1, 1 (1), 1 (1)
xor.ifnc r1, 1 (1), 1 (1)
or r0, -1 (31), -1 (31)
or r0, r0, r0
xor.setf -, elem_num, 0 (0)
or.ifz r2, r0, r0
nop.never 
or rep_all, r2, r2
or r0, r5, r5
or.setf -, r1, r1
or.ifzc r0, r0, r0
or.ifz r0, 0 (0), 0 (0)
or r3, r0, r0
// label: %call31.after
or r0, ra7, ra7
nop.never 
// label: %call32.%tmp.14
or r0, r0, r0
fmaxabs r0, r0, 0 (0)
or r0, r0, r0
nop.never 
// label: %call32.after
or r1, r0, r0
ldi r0, 1100480512
nop.never 
// label: %call33.%tmp.15
fsub.setf -, r0, r1
or.ifn r2, 1 (1), 1 (1)
xor.ifnc r2, 1 (1), 1 (1)
or r0, -1 (31), -1 (31)
or r0, r0, r0
xor.setf -, elem_num, 0 (0)
or.ifz r1, r0, r0
nop.never 
or rep_all, r1, r1
or r0, r5, r5
or.setf -, r2, r2
or.ifzc r0, r0, r0
or.ifz r0, 0 (0), 0 (0)
or r2, r0, r0
// label: %call33.after
or r0, r3, r3
xor.setf -, r0, 0 (0)
or.ifzc r1, 1 (1), 1 (1)
xor.ifz r1, 1 (1), 1 (1)
or r0, r2, r2
xor.setf -, r0, 0 (0)
or.ifzc r0, 1 (1), 1 (1)
xor.ifz r0, 1 (1), 1 (1)
and r0, r0, r1
or r1, r0, ra2
clz r0, 1 (1)
shl r1, r1, r0
clz r0, 1 (1)
asr r1, r1, r0
or r0, 0 (0), 0 (0)
or -, 1 (1), 1 (1)
or -, r1, r1
// label: %call40.%tmp.20
or r1, r0, r0
// label: %call40.after
clz r0, 1 (1)
asr rb0, r1, r0
nop.never 
xor r0, r1, rb0
sub r1, r0, rb0
clz r0, 1 (1)
asr ra0, rb1, r0
nop.never 
xor r0, rb1, ra0
sub ra2, r0, ra0
ldi r0, 65535
and r3, r1, r0
v8adds r0, 8 (8), 8 (8)
shr r2, r1, r0
ldi r0, 65535
and ra7, ra2, r0
v8adds r0, 8 (8), 8 (8)
shr r0, ra2, r0
mul24 r1, r3, ra7
mul24 r3, r3, r0
v8adds r0, 8 (8), 8 (8)
shl r3, r3, r0
nop.never 
add r1, r1, r3
mul24 r2, r2, ra7
v8adds r0, 8 (8), 8 (8)
shl r0, r2, r0
add r0, r1, r0
xor r1, rb0, ra0
xor r0, r0, r1
sub r0, r0, r1
shl r0, r0, 1 (1)
add r2, r0, ra1
clz r0, 1 (1)
asr r1, r2, r0
or r0, r2, r2
or -, 0 (0), 0 (0)
or -, r1, r1
// label: %call46.%tmp.20
or r0, r0, r0
nop.never 
// label: %call46.after
or r0, r0, r0
nop.never 
// label: %call47.%tmp.21
or r2, r0, r0
// label: %call47.after
ldi r0, 255
max r1, r0, r2
ldi r0, 255
xor.setf -, r1, r0
or.ifzc r1, 1 (1), 1 (1)
xor.ifz r1, 1 (1), 1 (1)
clz r0, 1 (1)
shl r1, r1, r0
clz r0, 1 (1)
asr r1, r1, r0
or r0, r2, r2
ldi.never -, 255
or -, r1, r1
// label: %call50.%tmp.20
or r0, r0, r0
nop.never 
// label: %call50.after
or r0, r0, r0
nop.never 
// label: %call51.%tmp.21
or r0, r0, r0
nop.never 
// label: %call51.after
or r2, r0, r0
or r0, ra6, ra6
or r1, ra5, ra5
// label: %_Z8vstore16ijPU3AS1i.1681692777.%tmp.22
or r0, r0, r0
shl r0, r0, 4 (4)
shl r0, r0, 2 (2)
add r0, r1, r0
or r0, r0, r0
or -, mutex_acq, mutex_acq
ldi vpw_setup, vpm_setup(size: 16 words, stride: 1 rows, address: h32(0))
or vpm, r2, r2
ldi vpw_setup, vdw_setup(rows: 1, elements: 16 words, address: h32(0))
ldi vpw_setup, vdw_setup(stride: 0)
or vpw_addr, r0, r0
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
nop.never 
or -, vpw_wait, vpw_wait
or mutex_rel, 1 (1), 1 (1)
// label: %_Z8vstore16ijPU3AS1i.1681692777.after
or r0, ra6, ra6
add ra0, r0, 1 (1)
v8adds r0, 8 (8), 8 (8)
shr r3, ra0, r0
ldi r0, 65535
and ra1, ra0, r0
v8adds r0, 8 (8), 8 (8)
shr r1, ra10, r0
ldi r0, 65535
and r2, ra10, r0
max r0, r3, r1
xor.setf -, r0, r3
or.ifzc ra2, 1 (1), 1 (1)
xor.ifz ra2, 1 (1), 1 (1)
xor.setf -, r3, r1
or.ifz r1, 1 (1), 1 (1)
xor.ifzc r1, 1 (1), 1 (1)
max r0, ra1, r2
xor.setf -, r0, ra1
or.ifzc r0, 1 (1), 1 (1)
xor.ifz r0, 1 (1), 1 (1)
and r0, r1, r0
or.setf -, ra2, r0
or.ifzc r0, 1 (1), 1 (1)
xor.ifz r0, 1 (1), 1 (1)
or.setf -, r0, r0
or.ifzc ra6, ra0, ra0
or.setf -, elem_num, r0
brr.ifallzc (pc+4) + -383 // to %tmp.3
nop.never 
nop.never 
nop.never 
brr.ifanyz (pc+4) + -391 // to %._crit_edge
nop.never 
nop.never 
nop.never 
// label: %end_of_function
or r0, unif, unif
or.setf -, elem_num, r0
brr.ifallzc (pc+4) + -1341 // to %start_of_function
nop.never 
nop.never 
nop.never 
not irq, qpu_num
nop.thrend.never 
nop.never 
nop.never 
