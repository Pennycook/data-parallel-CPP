// Copyright (C) 2023 Intel Corporation

// SPDX-License-Identifier: MIT

// These ".hpp" files are text from the book that are snipets
// that are not set up to be compiled as is.

// STREAM Triad: SIMD code generated by the compiler, where zmm0, zmm1 
// and zmm2 are SIMD vector registers. The vectorized loop is unrolled by 4
// to leverage the out-of-execution of instructions from Xeon CPU and to 
// hide memory load and store latency  

# %bb.0:                        # %entry
vbroadcastsd    %xmm0, %zmm0    # broadcast “scalar” to SIMD reg zmm0
movq    $-32, %rax
.p2align        4, 0x90
.LBB0_1:                        # %loop.19
                                # =>This Loop Header: Depth=1
vmovupd 256(%rdx,%rax,8), %zmm1 # load 8 elements from memory to zmm1 
vfmadd213pd     256(%rsi,%rax,8), %zmm0, %zmm1 # zmm1=(zmm0*zmm1)+mem
                                # perform SIMD FMA for 8 data elements 
                                # VC[id:8] = scalar*VB[id:8]+VA[id:8] 
vmovupd %zmm1, 256(%rdi,%rax,8) # store 8-element result to mem from zmm1  
                                # This SIMD loop body is unrolled by 4
vmovupd 320(%rdx,%rax,8), %zmm1 
vfmadd213pd     320(%rsi,%rax,8), %zmm0, %zmm1 # zmm1=(zmm0*zmm1)+mem
vmovupd %zmm1, 320(%rdi,%rax,8)
        
vmovupd 384(%rdx,%rax,8), %zmm1
vfmadd213pd     384(%rsi,%rax,8), %zmm0, %zmm1 # zmm1=(zmm0*zmm1)+mem
vmovupd %zmm1, 384(%rdi,%rax,8)
        
vmovupd 448(%rdx,%rax,8), %zmm1
vfmadd213pd     448(%rsi,%rax,8), %zmm0, %zmm1 # zmm1=(zmm0*zmm1)+mem
vmovupd %zmm1, 448(%rdi,%rax,8)
addq    $32, %rax
cmpq    $134217696, %rax        # imm = 0x7FFFFE0
jb      .LBB0_1