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
struct TYPE_4__ {scalar_t__ ApicId; } ;
struct TYPE_3__ {size_t IrqType; scalar_t__ DstApicId; size_t DstApicInt; } ;

/* Variables and functions */
 TYPE_2__* IOAPICMap ; 
 size_t IRQCount ; 
 TYPE_1__* IRQMap ; 
 scalar_t__ MP_APIC_ALL ; 

__attribute__((used)) static ULONG 
IOAPICGetIrqEntry(ULONG apic,
		  ULONG pin,
		  ULONG type)
{
   ULONG i;

   for (i = 0; i < IRQCount; i++)
   {
      if (IRQMap[i].IrqType == type &&
	  (IRQMap[i].DstApicId == IOAPICMap[apic].ApicId || IRQMap[i].DstApicId == MP_APIC_ALL) &&
	  IRQMap[i].DstApicInt == pin)
      {
         return i;
      }
   }
   return -1;
}