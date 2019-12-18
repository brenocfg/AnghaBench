#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG_PTR ;
typedef  int ULONG ;
typedef  int UCHAR ;
struct TYPE_4__ {int EFlags; } ;
struct TYPE_6__ {TYPE_1__ Tf; } ;
struct TYPE_5__ {int Limit; scalar_t__ Base; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  Mem ;
typedef  TYPE_2__ KDESCRIPTOR ;
typedef  int /*<<< orphan*/  IntDesc ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KdbBreakPointTemporary ; 
 TYPE_3__* KdbCurrentTrapFrame ; 
 int /*<<< orphan*/  KdbpInsertBreakPoint (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KdbpSafeReadMemory (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  __sidt (int*) ; 

BOOLEAN
KdbpStepIntoInstruction(
    ULONG_PTR Eip)
{
    KDESCRIPTOR Idtr = {0};
    UCHAR Mem[2];
    INT IntVect;
    ULONG IntDesc[2];
    ULONG_PTR TargetEip;

    /* Read memory */
    if (!NT_SUCCESS(KdbpSafeReadMemory(Mem, (PVOID)Eip, sizeof (Mem))))
    {
        /*KdbpPrint("Couldn't access memory at 0x%p\n", Eip);*/
        return FALSE;
    }

    /* Check for INT instruction */
    /* FIXME: Check for iret */
    if (Mem[0] == 0xcc)
        IntVect = 3;
    else if (Mem[0] == 0xcd)
        IntVect = Mem[1];
    else if (Mem[0] == 0xce && KdbCurrentTrapFrame->Tf.EFlags & (1<<11)) /* 1 << 11 is the overflow flag */
        IntVect = 4;
    else
        return FALSE;

    if (IntVect < 32) /* We should be informed about interrupts < 32 by the kernel, no need to breakpoint them */
    {
        return FALSE;
    }

    /* Read the interrupt descriptor table register  */
    __sidt(&Idtr.Limit);
    if (IntVect >= (Idtr.Limit + 1) / 8)
    {
        /*KdbpPrint("IDT does not contain interrupt vector %d\n.", IntVect);*/
        return TRUE;
    }

    /* Get the interrupt descriptor */
    if (!NT_SUCCESS(KdbpSafeReadMemory(IntDesc, (PVOID)(ULONG_PTR)(Idtr.Base + (IntVect * 8)), sizeof (IntDesc))))
    {
        /*KdbpPrint("Couldn't access memory at 0x%p\n", (ULONG_PTR)Idtr.Base + (IntVect * 8));*/
        return FALSE;
    }

    /* Check descriptor and get target eip (16 bit interrupt/trap gates not supported) */
    if ((IntDesc[1] & (1 << 15)) == 0) /* not present */
    {
        return FALSE;
    }
    if ((IntDesc[1] & 0x1f00) == 0x0500) /* Task gate */
    {
        /* FIXME: Task gates not supported */
        return FALSE;
    }
    else if (((IntDesc[1] & 0x1fe0) == 0x0e00) || /* 32 bit Interrupt gate */
             ((IntDesc[1] & 0x1fe0) == 0x0f00))   /* 32 bit Trap gate */
    {
        /* FIXME: Should the segment selector of the interrupt gate be checked? */
        TargetEip = (IntDesc[1] & 0xffff0000) | (IntDesc[0] & 0x0000ffff);
    }
    else
    {
        return FALSE;
    }

    /* Insert breakpoint */
    if (!NT_SUCCESS(KdbpInsertBreakPoint(TargetEip, KdbBreakPointTemporary, 0, 0, NULL, FALSE, NULL)))
        return FALSE;

    return TRUE;
}