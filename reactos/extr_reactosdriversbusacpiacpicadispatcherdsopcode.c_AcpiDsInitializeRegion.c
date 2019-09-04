#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiEvInitializeRegion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * AcpiNsGetAttachedObject (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiDsInitializeRegion (
    ACPI_HANDLE             ObjHandle)
{
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_STATUS             Status;


    ObjDesc = AcpiNsGetAttachedObject (ObjHandle);

    /* Namespace is NOT locked */

    Status = AcpiEvInitializeRegion (ObjDesc);
    return (Status);
}