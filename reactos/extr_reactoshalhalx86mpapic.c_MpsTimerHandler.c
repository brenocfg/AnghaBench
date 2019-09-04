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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PKIRQ_TRAPFRAME ;
typedef  int /*<<< orphan*/  KTRAP_FRAME ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  HalBeginSystemInterrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HalEndSystemInterrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KeGetCurrentProcessorNumber () ; 
 int /*<<< orphan*/  LOCAL_TIMER_VECTOR ; 
 int /*<<< orphan*/  MpsIRQTrapFrameToTrapFrame (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROFILE_LEVEL ; 
 int /*<<< orphan*/  _disable () ; 
 int /*<<< orphan*/  _enable () ; 

VOID
MpsTimerHandler(ULONG Vector, PKIRQ_TRAPFRAME Trapframe)
{
   KIRQL oldIrql;
   KTRAP_FRAME KernelTrapFrame;
#if 0
   ULONG CPU;
   static ULONG Count[MAX_CPU] = {0,};
#endif
   HalBeginSystemInterrupt(LOCAL_TIMER_VECTOR, 
                           PROFILE_LEVEL, 
			   &oldIrql);
   _enable();

#if 0
   CPU = ThisCPU();
   if ((Count[CPU] % 100) == 0)
   {
     DbgPrint("(%s:%d) MpsTimerHandler on CPU%d, irql = %d, epi = %x, KPCR = %x\n", __FILE__, __LINE__, CPU, oldIrql,Trapframe->Eip, KeGetPcr());
   }
   Count[CPU]++;
#endif

   /* FIXME: SMP is totally broken */
   MpsIRQTrapFrameToTrapFrame(Trapframe, &KernelTrapFrame);
   if (KeGetCurrentProcessorNumber() == 0)
   {
      //KeUpdateSystemTime(&KernelTrapFrame, oldIrql);
   }
   else
   {
      //KeUpdateRunTime(&KernelTrapFrame, oldIrql);
   }

   _disable();
   HalEndSystemInterrupt (oldIrql, 0);
}