#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
struct TYPE_4__ {size_t EntryCount; } ;
struct TYPE_3__ {size_t SrcBusId; size_t DstApicInt; size_t SrcBusIrq; } ;

/* Variables and functions */
 int* BUSMap ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 TYPE_2__* IOAPICMap ; 
 TYPE_1__* IRQMap ; 
#define  MP_BUS_EISA 131 
#define  MP_BUS_ISA 130 
#define  MP_BUS_MCA 129 
#define  MP_BUS_PCI 128 

__attribute__((used)) static ULONG 
Pin2Irq(ULONG idx,
	ULONG apic,
	ULONG pin)
{
   ULONG irq, i;
   ULONG bus = IRQMap[idx].SrcBusId;

   /*
    * Debugging check, we are in big trouble if this message pops up!
    */
   if (IRQMap[idx].DstApicInt != pin) 
   {
      DPRINT("broken BIOS or MPTABLE parser, ayiee!!\n");
   }

   switch (BUSMap[bus])
   {
      case MP_BUS_ISA: /* ISA pin */
      case MP_BUS_EISA:
      case MP_BUS_MCA:
	irq = IRQMap[idx].SrcBusIrq;
	break;

      case MP_BUS_PCI: /* PCI pin */
	 /*
	  * PCI IRQs are mapped in order
	  */
	 i = irq = 0;
	 while (i < apic)
	 {
	    irq += IOAPICMap[i++].EntryCount;
	 }
	 irq += pin;
	 break;
	
      default:
	 DPRINT("Unknown bus type %d.\n",bus);
	 irq = 0;
   }
   return irq;
}