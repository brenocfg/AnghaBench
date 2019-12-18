#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int SegGs; int SegFs; int SegEs; int SegDs; int Edi; int Esi; int Ebx; int Edx; int Ecx; int Eax; int Ebp; int Eip; int Esp; int SegCs; int EFlags; int SegSs; } ;
struct TYPE_4__ {scalar_t__ ContextFlags; int SegGs; int SegFs; int SegEs; int SegDs; int Edi; int Esi; int Ebx; int Edx; int Ecx; int Eax; int Ebp; int Eip; int Esp; int SegCs; int EFlags; int SegSs; } ;
typedef  TYPE_1__ CONTEXT ;

/* Variables and functions */
 scalar_t__ CONTEXT_FULL ; 
 int NTC_EFLAGS_BITS ; 
 int NTC_SEGMENT_BITS ; 
 TYPE_2__ continueContext ; 
 int /*<<< orphan*/  jmpbuf ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

void check(CONTEXT * pContext)
{
#ifdef _M_IX86
    ok(pContext->ContextFlags == CONTEXT_FULL,
       "ContextFlags=0x%lx\n", pContext->ContextFlags);

    /* Random data segments */
    ok((pContext->SegGs & NTC_SEGMENT_BITS) ==
       (continueContext.SegGs & NTC_SEGMENT_BITS),
       "SegGs=0x%lx / 0x%lx\n", pContext->SegGs, continueContext.SegGs);

    ok((pContext->SegFs & NTC_SEGMENT_BITS) ==
       (continueContext.SegFs & NTC_SEGMENT_BITS),
       "SegFs=0x%lx / 0x%lx\n", pContext->SegFs, continueContext.SegFs);

    ok((pContext->SegEs & NTC_SEGMENT_BITS) ==
       (continueContext.SegEs & NTC_SEGMENT_BITS),
       "SegEs=0x%lx / 0x%lx\n", pContext->SegEs, continueContext.SegEs);

    ok((pContext->SegDs & NTC_SEGMENT_BITS) ==
       (continueContext.SegDs & NTC_SEGMENT_BITS),
       "SegDs=0x%lx / 0x%lx\n", pContext->SegDs, continueContext.SegDs);

    /* Integer registers */
    ok(pContext->Edi == continueContext.Edi,
       "Edi: 0x%lx != 0x%lx\n", pContext->Edi, continueContext.Edi);
    ok(pContext->Esi == continueContext.Esi,
       "Esi: 0x%lx != 0x%lx\n", pContext->Esi, continueContext.Esi);
    ok(pContext->Ebx == continueContext.Ebx,
       "Ebx: 0x%lx != 0x%lx\n", pContext->Ebx, continueContext.Ebx);
    ok(pContext->Edx == continueContext.Edx,
       "Edx: 0x%lx != 0x%lx\n", pContext->Edx, continueContext.Edx);
    ok(pContext->Ecx == continueContext.Ecx,
       "Ecx: 0x%lx != 0x%lx\n", pContext->Ecx, continueContext.Ecx);
    ok(pContext->Eax == continueContext.Eax,
       "Eax: 0x%lx != 0x%lx\n", pContext->Eax, continueContext.Eax);

    /* Control registers and segments */
    ok(pContext->Ebp == continueContext.Ebp,
       "Ebp: 0x%lx != 0x%lx\n", pContext->Ebp, continueContext.Ebp);
    ok(pContext->Eip == continueContext.Eip,
       "Eip: 0x%lx != 0x%lx\n", pContext->Eip, continueContext.Eip);
    ok(pContext->Esp == continueContext.Esp,
       "Esp: 0x%lx != 0x%lx\n", pContext->Esp, continueContext.Esp);

    ok((pContext->SegCs & NTC_SEGMENT_BITS) ==
       (continueContext.SegCs & NTC_SEGMENT_BITS),
       "SegCs: 0x%lx != 0x%lx\n", pContext->SegCs, continueContext.SegCs);

    ok((pContext->EFlags & NTC_EFLAGS_BITS) ==
       (continueContext.EFlags & NTC_EFLAGS_BITS),
       "EFlags: 0x%lx != 0x%lx\n", pContext->EFlags, continueContext.EFlags);

    ok((pContext->SegSs & NTC_SEGMENT_BITS) ==
       (continueContext.SegSs & NTC_SEGMENT_BITS),
       "SegSs: 0x%lx != 0x%lx\n", pContext->SegSs, continueContext.SegSs);
#endif

    /* Return where we came from */
    longjmp(jmpbuf, 1);
}