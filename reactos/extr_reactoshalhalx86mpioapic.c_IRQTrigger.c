#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
struct TYPE_2__ {size_t SrcBusId; int IrqFlag; } ;

/* Variables and functions */
 int /*<<< orphan*/ * BUSMap ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 TYPE_1__* IRQMap ; 
#define  MP_BUS_EISA 131 
#define  MP_BUS_ISA 130 
#define  MP_BUS_MCA 129 
#define  MP_BUS_PCI 128 
 size_t default_EISA_trigger (size_t) ; 
 size_t default_ISA_trigger (size_t) ; 
 size_t default_MCA_trigger (size_t) ; 
 size_t default_PCI_trigger (size_t) ; 

__attribute__((used)) static ULONG 
IRQTrigger(ULONG idx)
{
   ULONG bus = IRQMap[idx].SrcBusId;
   ULONG trigger;

   /*
    * Determine IRQ trigger mode (edge or level sensitive):
    */
   switch ((IRQMap[idx].IrqFlag >> 2) & 3)
   {
      case 0: /* conforms, ie. bus-type dependent */
	 {
            switch (BUSMap[bus])
	    {
	       case MP_BUS_ISA: /* ISA pin */
	          trigger = default_ISA_trigger(idx);
		  break;

	       case MP_BUS_EISA: /* EISA pin */
		  trigger = default_EISA_trigger(idx);
		  break;
		
	       case MP_BUS_PCI: /* PCI pin */
		  trigger = default_PCI_trigger(idx);
		  break;

               case MP_BUS_MCA: /* MCA pin */
		  trigger = default_MCA_trigger(idx);
		  break;
		
               default:
                  DPRINT("Broken BIOS!!\n");
		  trigger = 1;
	    }
	 }
	 break;

      case 1: /* edge */
	 trigger = 0;
	 break;

      case 2: /* reserved */
	 DPRINT("Broken BIOS!!\n");
	 trigger = 1;
	 break;

      case 3: /* level */
 	 trigger = 1;
	 break;
	
      default: /* invalid */
	 DPRINT("Broken BIOS!!\n");
	 trigger = 0;					
   }
   return trigger;
}