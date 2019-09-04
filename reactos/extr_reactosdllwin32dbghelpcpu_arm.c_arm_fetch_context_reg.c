#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,unsigned int) ; 

__attribute__((used)) static void* arm_fetch_context_reg(CONTEXT* ctx, unsigned regno, unsigned* size)
{
#ifdef __arm__
    switch (regno)
    {
    case CV_ARM_R0 +  0: *size = sizeof(ctx->R0); return &ctx->R0;
    case CV_ARM_R0 +  1: *size = sizeof(ctx->R1); return &ctx->R1;
    case CV_ARM_R0 +  2: *size = sizeof(ctx->R2); return &ctx->R2;
    case CV_ARM_R0 +  3: *size = sizeof(ctx->R3); return &ctx->R3;
    case CV_ARM_R0 +  4: *size = sizeof(ctx->R4); return &ctx->R4;
    case CV_ARM_R0 +  5: *size = sizeof(ctx->R5); return &ctx->R5;
    case CV_ARM_R0 +  6: *size = sizeof(ctx->R6); return &ctx->R6;
    case CV_ARM_R0 +  7: *size = sizeof(ctx->R7); return &ctx->R7;
    case CV_ARM_R0 +  8: *size = sizeof(ctx->R8); return &ctx->R8;
    case CV_ARM_R0 +  9: *size = sizeof(ctx->R9); return &ctx->R9;
    case CV_ARM_R0 + 10: *size = sizeof(ctx->R10); return &ctx->R10;
#ifdef __REACTOS__
    case CV_ARM_R0 + 11: *size = sizeof(ctx->R11); return &ctx->R11;
    case CV_ARM_R0 + 12: *size = sizeof(ctx->R12); return &ctx->R12;
#else
    case CV_ARM_R0 + 11: *size = sizeof(ctx->Fp); return &ctx->Fp;
    case CV_ARM_R0 + 12: *size = sizeof(ctx->Ip); return &ctx->Ip;
#endif

    case CV_ARM_SP: *size = sizeof(ctx->Sp); return &ctx->Sp;
    case CV_ARM_LR: *size = sizeof(ctx->Lr); return &ctx->Lr;
    case CV_ARM_PC: *size = sizeof(ctx->Pc); return &ctx->Pc;
    case CV_ARM_CPSR: *size = sizeof(ctx->Cpsr); return &ctx->Cpsr;
    }
#endif
    FIXME("Unknown register %x\n", regno);
    return NULL;
}