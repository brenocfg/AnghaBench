#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  void* USHORT ;
struct TYPE_6__ {int /*<<< orphan*/  Eflags; int /*<<< orphan*/  Cs; int /*<<< orphan*/  Eip; int /*<<< orphan*/  Edi; int /*<<< orphan*/  Esi; int /*<<< orphan*/  Ebp; int /*<<< orphan*/  Esp; int /*<<< orphan*/  Ebx; int /*<<< orphan*/  Edx; int /*<<< orphan*/  Ecx; int /*<<< orphan*/  Eax; scalar_t__ Ds; scalar_t__ Es; scalar_t__ Fs; scalar_t__ Gs; } ;
struct TYPE_5__ {int /*<<< orphan*/  EFlags; int /*<<< orphan*/  SegCs; int /*<<< orphan*/  Eip; int /*<<< orphan*/  Edi; int /*<<< orphan*/  Esi; int /*<<< orphan*/  Ebp; int /*<<< orphan*/  HardwareEsp; int /*<<< orphan*/  Ebx; int /*<<< orphan*/  Edx; int /*<<< orphan*/  Ecx; int /*<<< orphan*/  Eax; void* SegDs; void* SegEs; void* SegFs; void* SegGs; } ;
typedef  TYPE_1__* PKTRAP_FRAME ;
typedef  TYPE_2__* PKIRQ_TRAPFRAME ;

/* Variables and functions */

VOID
MpsIRQTrapFrameToTrapFrame(PKIRQ_TRAPFRAME IrqTrapFrame,
			   PKTRAP_FRAME TrapFrame)
{
#ifdef _M_AMD64
    UNIMPLEMENTED;
#else
   TrapFrame->SegGs     = (USHORT)IrqTrapFrame->Gs;
   TrapFrame->SegFs     = (USHORT)IrqTrapFrame->Fs;
   TrapFrame->SegEs     = (USHORT)IrqTrapFrame->Es;
   TrapFrame->SegDs     = (USHORT)IrqTrapFrame->Ds;
   TrapFrame->Eax    = IrqTrapFrame->Eax;
   TrapFrame->Ecx    = IrqTrapFrame->Ecx;
   TrapFrame->Edx    = IrqTrapFrame->Edx;
   TrapFrame->Ebx    = IrqTrapFrame->Ebx;
   TrapFrame->HardwareEsp    = IrqTrapFrame->Esp;
   TrapFrame->Ebp    = IrqTrapFrame->Ebp;
   TrapFrame->Esi    = IrqTrapFrame->Esi;
   TrapFrame->Edi    = IrqTrapFrame->Edi;
   TrapFrame->Eip    = IrqTrapFrame->Eip;
   TrapFrame->SegCs     = IrqTrapFrame->Cs;
   TrapFrame->EFlags = IrqTrapFrame->Eflags;
#endif
}