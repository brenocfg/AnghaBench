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
struct TYPE_5__ {int srr1; int /*<<< orphan*/  dsisr; int /*<<< orphan*/  dar; int /*<<< orphan*/  srr0; int /*<<< orphan*/  xer; int /*<<< orphan*/  ctr; int /*<<< orphan*/  cr; int /*<<< orphan*/  lr; int /*<<< orphan*/  gpr; } ;
typedef  TYPE_1__ ppc_trap_frame_t ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int Msr; int /*<<< orphan*/  Dr1; int /*<<< orphan*/  Dr0; int /*<<< orphan*/  Iar; int /*<<< orphan*/  Xer; int /*<<< orphan*/  Ctr; int /*<<< orphan*/  Cr; int /*<<< orphan*/  Lr; int /*<<< orphan*/  Gpr0; } ;
typedef  TYPE_2__* PKTRAP_FRAME ;

/* Variables and functions */
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

VOID MmpPpcTrapFrameToTrapFrame(ppc_trap_frame_t *frame, PKTRAP_FRAME Tf)
{
    RtlCopyMemory(&Tf->Gpr0, frame->gpr, 12 * sizeof(ULONG));
    Tf->Lr = frame->lr;
    Tf->Cr = frame->cr;
    Tf->Ctr = frame->ctr;
    Tf->Xer = frame->xer;
    Tf->Iar = frame->srr0;
    Tf->Msr = frame->srr1 & 0xffff;
    Tf->Dr0 = frame->dar;
    Tf->Dr1 = frame->dsisr;
}