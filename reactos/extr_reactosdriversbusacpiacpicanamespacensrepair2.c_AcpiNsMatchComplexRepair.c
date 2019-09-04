#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  Ascii; } ;
struct TYPE_9__ {TYPE_1__ Name; } ;
struct TYPE_8__ {int /*<<< orphan*/  Name; scalar_t__ RepairFunction; } ;
typedef  TYPE_2__ ACPI_REPAIR_INFO ;
typedef  TYPE_3__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* AcpiNsRepairableNames ; 

__attribute__((used)) static const ACPI_REPAIR_INFO *
AcpiNsMatchComplexRepair (
    ACPI_NAMESPACE_NODE     *Node)
{
    const ACPI_REPAIR_INFO  *ThisName;


    /* Search info table for a repairable predefined method/object name */

    ThisName = AcpiNsRepairableNames;
    while (ThisName->RepairFunction)
    {
        if (ACPI_COMPARE_NAMESEG (Node->Name.Ascii, ThisName->Name))
        {
            return (ThisName);
        }

        ThisName++;
    }

    return (NULL); /* Not found */
}