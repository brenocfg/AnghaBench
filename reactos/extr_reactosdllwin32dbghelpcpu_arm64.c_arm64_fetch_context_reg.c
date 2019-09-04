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

__attribute__((used)) static void* arm64_fetch_context_reg(CONTEXT* ctx, unsigned regno, unsigned* size)
{
#ifdef __aarch64__
    switch (regno)
    {
    case CV_ARM64_X0 +  0:
    case CV_ARM64_X0 +  1:
    case CV_ARM64_X0 +  2:
    case CV_ARM64_X0 +  3:
    case CV_ARM64_X0 +  4:
    case CV_ARM64_X0 +  5:
    case CV_ARM64_X0 +  6:
    case CV_ARM64_X0 +  7:
    case CV_ARM64_X0 +  8:
    case CV_ARM64_X0 +  9:
    case CV_ARM64_X0 + 10:
    case CV_ARM64_X0 + 11:
    case CV_ARM64_X0 + 12:
    case CV_ARM64_X0 + 13:
    case CV_ARM64_X0 + 14:
    case CV_ARM64_X0 + 15:
    case CV_ARM64_X0 + 16:
    case CV_ARM64_X0 + 17:
    case CV_ARM64_X0 + 18:
    case CV_ARM64_X0 + 19:
    case CV_ARM64_X0 + 20:
    case CV_ARM64_X0 + 21:
    case CV_ARM64_X0 + 22:
    case CV_ARM64_X0 + 23:
    case CV_ARM64_X0 + 24:
    case CV_ARM64_X0 + 25:
    case CV_ARM64_X0 + 26:
    case CV_ARM64_X0 + 27:
    case CV_ARM64_X0 + 28: *size = sizeof(ctx->u.X[0]); return &ctx->u.X[regno - CV_ARM64_X0];
    case CV_ARM64_PSTATE:  *size = sizeof(ctx->Cpsr);   return &ctx->Cpsr;
    case CV_ARM64_FP:      *size = sizeof(ctx->u.s.Fp); return &ctx->u.s.Fp;
    case CV_ARM64_LR:      *size = sizeof(ctx->u.s.Lr); return &ctx->u.s.Lr;
    case CV_ARM64_SP:      *size = sizeof(ctx->Sp);     return &ctx->Sp;
    case CV_ARM64_PC:      *size = sizeof(ctx->Pc);     return &ctx->Pc;
    }
#endif
    FIXME("Unknown register %x\n", regno);
    return NULL;
}