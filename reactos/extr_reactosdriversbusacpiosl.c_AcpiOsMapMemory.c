#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {scalar_t__ QuadPart; } ;
typedef  void* PVOID ;
typedef  TYPE_1__ PHYSICAL_ADDRESS ;
typedef  int /*<<< orphan*/  ACPI_SIZE ;
typedef  scalar_t__ ACPI_PHYSICAL_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 void* MmMapIoSpace (TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MmNonCached ; 

void *
AcpiOsMapMemory (
    ACPI_PHYSICAL_ADDRESS   phys,
    ACPI_SIZE               length)
{
    PHYSICAL_ADDRESS Address;
    PVOID Ptr;

    DPRINT("AcpiOsMapMemory(phys 0x%p  size 0x%X)\n", phys, length);

    Address.QuadPart = (ULONG)phys;
    Ptr = MmMapIoSpace(Address, length, MmNonCached);
    if (!Ptr)
    {
        DPRINT1("Mapping failed\n");
    }

    return Ptr;
}