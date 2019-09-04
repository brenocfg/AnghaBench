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
struct TYPE_4__ {int Flags; scalar_t__ Address; } ;
typedef  TYPE_1__ ACPI_TABLE_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_PHYSADDR_TO_PTR (scalar_t__) ; 
 scalar_t__ ACPI_PTR_TO_PHYSADDR (int /*<<< orphan*/ *) ; 
 int ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL ; 
 int ACPI_TABLE_ORIGIN_MASK ; 
 int /*<<< orphan*/  AcpiTbInvalidateTable (TYPE_1__*) ; 
 int /*<<< orphan*/  TbUninstallTable ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiTbUninstallTable (
    ACPI_TABLE_DESC         *TableDesc)
{

    ACPI_FUNCTION_TRACE (TbUninstallTable);


    /* Table must be installed */

    if (!TableDesc->Address)
    {
        return_VOID;
    }

    AcpiTbInvalidateTable (TableDesc);

    if ((TableDesc->Flags & ACPI_TABLE_ORIGIN_MASK) ==
        ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL)
    {
        ACPI_FREE (ACPI_PHYSADDR_TO_PTR (TableDesc->Address));
    }

    TableDesc->Address = ACPI_PTR_TO_PHYSADDR (NULL);
    return_VOID;
}