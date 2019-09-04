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
 size_t default_EISA_polarity (size_t) ; 
 size_t default_ISA_polarity (size_t) ; 
 size_t default_MCA_polarity (size_t) ; 
 size_t default_PCI_polarity (size_t) ; 

__attribute__((used)) static ULONG 
IRQPolarity(ULONG idx)
{
   ULONG bus = IRQMap[idx].SrcBusId;
   ULONG polarity;

   /*
    * Determine IRQ line polarity (high active or low active):
    */
   switch (IRQMap[idx].IrqFlag & 3)
   {
      case 0: /* conforms, ie. bus-type dependent polarity */
         {
            switch (BUSMap[bus])
	    {
	       case MP_BUS_ISA: /* ISA pin */
		  polarity = default_ISA_polarity(idx);
		  break;
		  
	       case MP_BUS_EISA: /* EISA pin */
		  polarity = default_EISA_polarity(idx);
		  break;
		
	       case MP_BUS_PCI: /* PCI pin */
		  polarity = default_PCI_polarity(idx);
		  break;

	       case MP_BUS_MCA: /* MCA pin */
                  polarity = default_MCA_polarity(idx);
		  break;
		
	       default:
		  DPRINT("Broken BIOS!!\n");
		  polarity = 1;
	    }
	 }
	 break;

      case 1: /* high active */
	 polarity = 0;
	 break;

      case 2: /* reserved */
	 DPRINT("Broken BIOS!!\n");
	 polarity = 1;
	 break;

      case 3: /* low active */
         polarity = 1;
	 break;

      default: /* invalid */
	 DPRINT("Broken BIOS!!\n");
	 polarity = 1;
   }
   return polarity;
}