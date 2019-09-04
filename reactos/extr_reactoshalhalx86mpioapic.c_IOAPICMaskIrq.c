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
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t ULONG ;
struct TYPE_4__ {int logical_dest; } ;
struct TYPE_5__ {TYPE_1__ logical; } ;
struct TYPE_6__ {int mask; TYPE_2__ dest; } ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  TYPE_3__ IOAPIC_ROUTE_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  IOAPICRead (size_t,scalar_t__) ; 
 int /*<<< orphan*/  IOAPICWrite (size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ IOAPIC_REDTBL ; 
 size_t* IrqApicMap ; 
 int KeGetCurrentProcessorNumber () ; 

VOID IOAPICMaskIrq(ULONG Irq)
{
   IOAPIC_ROUTE_ENTRY Entry;
   ULONG Apic = IrqApicMap[Irq];

   *(((PULONG)&Entry)+0) = IOAPICRead(Apic, IOAPIC_REDTBL+2*Irq);
   *(((PULONG)&Entry)+1) = IOAPICRead(Apic, IOAPIC_REDTBL+2*Irq+1);
   Entry.dest.logical.logical_dest &= ~(1 << KeGetCurrentProcessorNumber());
   if (Entry.dest.logical.logical_dest == 0)
   {
      Entry.mask = 1;
   }
   IOAPICWrite(Apic, IOAPIC_REDTBL+2*Irq+1, *(((PULONG)&Entry)+1));
   IOAPICWrite(Apic, IOAPIC_REDTBL+2*Irq, *(((PULONG)&Entry)+0));
}