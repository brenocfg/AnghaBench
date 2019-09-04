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
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t ULONG ;
struct TYPE_2__ {scalar_t__ ApicAddress; } ;
typedef  size_t* PULONG ;

/* Variables and functions */
 TYPE_1__* IOAPICMap ; 
 size_t IOAPIC_IOWIN ; 

VOID IOAPICWrite(ULONG Apic, ULONG Offset, ULONG Value)
{
  PULONG Base;

  Base = (PULONG)IOAPICMap[Apic].ApicAddress;
  *Base = Offset;
  *((PULONG)((ULONG)Base + IOAPIC_IOWIN)) = Value;
}