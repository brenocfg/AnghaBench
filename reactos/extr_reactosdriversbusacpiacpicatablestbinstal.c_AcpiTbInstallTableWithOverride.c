#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_9__ {int /*<<< orphan*/ * Tables; } ;
struct TYPE_8__ {int /*<<< orphan*/  Revision; } ;
struct TYPE_7__ {TYPE_2__* Pointer; int /*<<< orphan*/  Address; int /*<<< orphan*/  Flags; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  TYPE_1__ ACPI_TABLE_DESC ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 size_t AcpiGbl_DsdtIndex ; 
 TYPE_6__ AcpiGbl_RootTableList ; 
 int /*<<< orphan*/  AcpiTbGetNextTableDescriptor (size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiTbInitTableDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiTbOverrideTable (TYPE_1__*) ; 
 int /*<<< orphan*/  AcpiTbPrintTableHeader (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiUtSetIntegerWidth (int /*<<< orphan*/ ) ; 

void
AcpiTbInstallTableWithOverride (
    ACPI_TABLE_DESC         *NewTableDesc,
    BOOLEAN                 Override,
    UINT32                  *TableIndex)
{
    UINT32                  i;
    ACPI_STATUS             Status;


    Status = AcpiTbGetNextTableDescriptor (&i, NULL);
    if (ACPI_FAILURE (Status))
    {
        return;
    }

    /*
     * ACPI Table Override:
     *
     * Before we install the table, let the host OS override it with a new
     * one if desired. Any table within the RSDT/XSDT can be replaced,
     * including the DSDT which is pointed to by the FADT.
     */
    if (Override)
    {
        AcpiTbOverrideTable (NewTableDesc);
    }

    AcpiTbInitTableDescriptor (&AcpiGbl_RootTableList.Tables[i],
        NewTableDesc->Address, NewTableDesc->Flags, NewTableDesc->Pointer);

    AcpiTbPrintTableHeader (NewTableDesc->Address, NewTableDesc->Pointer);

    /* This synchronizes AcpiGbl_DsdtIndex */

    *TableIndex = i;

    /* Set the global integer width (based upon revision of the DSDT) */

    if (i == AcpiGbl_DsdtIndex)
    {
        AcpiUtSetIntegerWidth (NewTableDesc->Pointer->Revision);
    }
}