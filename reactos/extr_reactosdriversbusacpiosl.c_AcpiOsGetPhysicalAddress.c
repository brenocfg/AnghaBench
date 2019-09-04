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
struct TYPE_3__ {scalar_t__ QuadPart; } ;
typedef  TYPE_1__ PHYSICAL_ADDRESS ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  scalar_t__ ACPI_PHYSICAL_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 TYPE_1__ MmGetPhysicalAddress (void*) ; 

ACPI_STATUS
AcpiOsGetPhysicalAddress(
    void *LogicalAddress,
    ACPI_PHYSICAL_ADDRESS *PhysicalAddress)
{
    PHYSICAL_ADDRESS PhysAddr;

    if (!LogicalAddress || !PhysicalAddress)
    {
        DPRINT1("Bad parameter\n");
        return AE_BAD_PARAMETER;
    }

    PhysAddr = MmGetPhysicalAddress(LogicalAddress);

    *PhysicalAddress = (ACPI_PHYSICAL_ADDRESS)PhysAddr.QuadPart;

    return AE_OK;
}