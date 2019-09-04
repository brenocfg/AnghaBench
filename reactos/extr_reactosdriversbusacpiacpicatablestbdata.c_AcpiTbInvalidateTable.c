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
struct TYPE_3__ {int /*<<< orphan*/ * Pointer; int /*<<< orphan*/  Flags; int /*<<< orphan*/  Length; } ;
typedef  TYPE_1__ ACPI_TABLE_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiTbReleaseTable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TbInvalidateTable ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiTbInvalidateTable (
    ACPI_TABLE_DESC         *TableDesc)
{

    ACPI_FUNCTION_TRACE (TbInvalidateTable);


    /* Table must be validated */

    if (!TableDesc->Pointer)
    {
        return_VOID;
    }

    AcpiTbReleaseTable (TableDesc->Pointer, TableDesc->Length,
        TableDesc->Flags);
    TableDesc->Pointer = NULL;

    return_VOID;
}