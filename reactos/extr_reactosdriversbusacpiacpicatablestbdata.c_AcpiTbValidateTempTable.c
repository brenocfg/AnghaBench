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
struct TYPE_4__ {int Length; int /*<<< orphan*/  Pointer; } ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;
typedef  TYPE_1__ ACPI_TABLE_DESC ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiGbl_EnableTableValidation ; 
 int /*<<< orphan*/  AcpiTbValidateTable (TYPE_1__*) ; 

ACPI_STATUS
AcpiTbValidateTempTable (
    ACPI_TABLE_DESC         *TableDesc)
{

    if (!TableDesc->Pointer && !AcpiGbl_EnableTableValidation)
    {
        /*
         * Only validates the header of the table.
         * Note that Length contains the size of the mapping after invoking
         * this work around, this value is required by
         * AcpiTbReleaseTempTable().
         * We can do this because in AcpiInitTableDescriptor(), the Length
         * field of the installed descriptor is filled with the actual
         * table length obtaining from the table header.
         */
        TableDesc->Length = sizeof (ACPI_TABLE_HEADER);
    }

    return (AcpiTbValidateTable (TableDesc));
}