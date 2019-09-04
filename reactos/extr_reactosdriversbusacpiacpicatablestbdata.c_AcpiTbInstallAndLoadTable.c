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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PHYSICAL_ADDRESS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGbl_RootNode ; 
 int /*<<< orphan*/  AcpiTbInstallStandardTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiTbLoadTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TbInstallAndLoadTable ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiTbInstallAndLoadTable (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT8                   Flags,
    BOOLEAN                 Override,
    UINT32                  *TableIndex)
{
    ACPI_STATUS             Status;
    UINT32                  i;


    ACPI_FUNCTION_TRACE (TbInstallAndLoadTable);


    /* Install the table and load it into the namespace */

    Status = AcpiTbInstallStandardTable (Address, Flags, TRUE,
        Override, &i);
    if (ACPI_FAILURE (Status))
    {
        goto Exit;
    }

    Status = AcpiTbLoadTable (i, AcpiGbl_RootNode);

Exit:
    *TableIndex = i;
    return_ACPI_STATUS (Status);
}