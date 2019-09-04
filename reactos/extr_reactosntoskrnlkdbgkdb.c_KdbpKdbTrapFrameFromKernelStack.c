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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  PKDB_KTRAP_FRAME ;
typedef  int /*<<< orphan*/  KDB_KTRAP_FRAME ;

/* Variables and functions */
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static VOID
KdbpKdbTrapFrameFromKernelStack(
    PVOID KernelStack,
    PKDB_KTRAP_FRAME KdbTrapFrame)
{
    ULONG_PTR *StackPtr;

    RtlZeroMemory(KdbTrapFrame, sizeof(KDB_KTRAP_FRAME));
    StackPtr = (ULONG_PTR *) KernelStack;
#ifdef _M_IX86
    KdbTrapFrame->Tf.Ebp = StackPtr[3];
    KdbTrapFrame->Tf.Edi = StackPtr[4];
    KdbTrapFrame->Tf.Esi = StackPtr[5];
    KdbTrapFrame->Tf.Ebx = StackPtr[6];
    KdbTrapFrame->Tf.Eip = StackPtr[7];
    KdbTrapFrame->Tf.HardwareEsp = (ULONG) (StackPtr + 8);
    KdbTrapFrame->Tf.HardwareSegSs = KGDT_R0_DATA;
    KdbTrapFrame->Tf.SegCs = KGDT_R0_CODE;
    KdbTrapFrame->Tf.SegDs = KGDT_R0_DATA;
    KdbTrapFrame->Tf.SegEs = KGDT_R0_DATA;
    KdbTrapFrame->Tf.SegGs = KGDT_R0_DATA;
#endif

    /* FIXME: what about the other registers??? */
}