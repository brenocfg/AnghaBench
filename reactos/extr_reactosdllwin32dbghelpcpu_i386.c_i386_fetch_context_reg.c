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

__attribute__((used)) static void* i386_fetch_context_reg(CONTEXT* ctx, unsigned regno, unsigned* size)
{
#ifdef __i386__
    switch (regno)
    {
    case CV_REG_EAX: *size = sizeof(ctx->Eax); return &ctx->Eax;
    case CV_REG_EDX: *size = sizeof(ctx->Edx); return &ctx->Edx;
    case CV_REG_ECX: *size = sizeof(ctx->Ecx); return &ctx->Ecx;
    case CV_REG_EBX: *size = sizeof(ctx->Ebx); return &ctx->Ebx;
    case CV_REG_ESI: *size = sizeof(ctx->Esi); return &ctx->Esi;
    case CV_REG_EDI: *size = sizeof(ctx->Edi); return &ctx->Edi;
    case CV_REG_EBP: *size = sizeof(ctx->Ebp); return &ctx->Ebp;
    case CV_REG_ESP: *size = sizeof(ctx->Esp); return &ctx->Esp;
    case CV_REG_EIP: *size = sizeof(ctx->Eip); return &ctx->Eip;

    /* These are x87 floating point registers... They do not match a C type in
     * the Linux ABI, so hardcode their 80-bitness. */
    case CV_REG_ST0 + 0: *size = 10; return &ctx->FloatSave.RegisterArea[0*10];
    case CV_REG_ST0 + 1: *size = 10; return &ctx->FloatSave.RegisterArea[1*10];
    case CV_REG_ST0 + 2: *size = 10; return &ctx->FloatSave.RegisterArea[2*10];
    case CV_REG_ST0 + 3: *size = 10; return &ctx->FloatSave.RegisterArea[3*10];
    case CV_REG_ST0 + 4: *size = 10; return &ctx->FloatSave.RegisterArea[4*10];
    case CV_REG_ST0 + 5: *size = 10; return &ctx->FloatSave.RegisterArea[5*10];
    case CV_REG_ST0 + 6: *size = 10; return &ctx->FloatSave.RegisterArea[6*10];
    case CV_REG_ST0 + 7: *size = 10; return &ctx->FloatSave.RegisterArea[7*10];

    case CV_REG_CTRL: *size = sizeof(DWORD); return &ctx->FloatSave.ControlWord;
    case CV_REG_STAT: *size = sizeof(DWORD); return &ctx->FloatSave.StatusWord;
    case CV_REG_TAG:  *size = sizeof(DWORD); return &ctx->FloatSave.TagWord;
    case CV_REG_FPCS: *size = sizeof(DWORD); return &ctx->FloatSave.ErrorSelector;
    case CV_REG_FPIP: *size = sizeof(DWORD); return &ctx->FloatSave.ErrorOffset;
    case CV_REG_FPDS: *size = sizeof(DWORD); return &ctx->FloatSave.DataSelector;
    case CV_REG_FPDO: *size = sizeof(DWORD); return &ctx->FloatSave.DataOffset;

    case CV_REG_EFLAGS: *size = sizeof(ctx->EFlags); return &ctx->EFlags;
    case CV_REG_ES: *size = sizeof(ctx->SegEs); return &ctx->SegEs;
    case CV_REG_CS: *size = sizeof(ctx->SegCs); return &ctx->SegCs;
    case CV_REG_SS: *size = sizeof(ctx->SegSs); return &ctx->SegSs;
    case CV_REG_DS: *size = sizeof(ctx->SegDs); return &ctx->SegDs;
    case CV_REG_FS: *size = sizeof(ctx->SegFs); return &ctx->SegFs;
    case CV_REG_GS: *size = sizeof(ctx->SegGs); return &ctx->SegGs;

    }
#endif
    FIXME("Unknown register %x\n", regno);
    return NULL;
}