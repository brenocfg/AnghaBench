#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int IrqFlag; int /*<<< orphan*/  DstApicInt; int /*<<< orphan*/  DstApicId; int /*<<< orphan*/  SrcBusIrq; int /*<<< orphan*/  SrcBusId; int /*<<< orphan*/  IrqType; } ;
typedef  TYPE_1__* PMP_CONFIGURATION_INTSRC ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 size_t IRQCount ; 
 TYPE_1__* IRQMap ; 
 size_t MAX_IRQ_SOURCE ; 

__attribute__((used)) static VOID 
HaliMPIntSrcInfo(PMP_CONFIGURATION_INTSRC m)
{
  DPRINT("Int: type %d, pol %d, trig %d, bus %d,"
         " IRQ %02x, APIC ID %x, APIC INT %02x\n",
         m->IrqType, m->IrqFlag & 3,
         (m->IrqFlag >> 2) & 3, m->SrcBusId,
         m->SrcBusIrq, m->DstApicId, m->DstApicInt);
  if (IRQCount > MAX_IRQ_SOURCE) 
  {
    DPRINT1("Max # of irq sources exceeded!!\n");
    ASSERT(FALSE);
  }

  IRQMap[IRQCount] = *m;
  IRQCount++;
}