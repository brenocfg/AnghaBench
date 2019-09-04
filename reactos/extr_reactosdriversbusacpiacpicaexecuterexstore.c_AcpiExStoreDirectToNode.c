#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  Type; } ;
struct TYPE_12__ {int /*<<< orphan*/  Type; } ;
struct TYPE_13__ {TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_3__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiNsAttachObject (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtCopyIobjectToIobject (TYPE_2__*,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtGetObjectTypeName (TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiUtGetTypeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_2__*) ; 
 int /*<<< orphan*/  ExStoreDirectToNode ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiExStoreDirectToNode (
    ACPI_OPERAND_OBJECT     *SourceDesc,
    ACPI_NAMESPACE_NODE     *Node,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status;
    ACPI_OPERAND_OBJECT     *NewDesc;


    ACPI_FUNCTION_TRACE (ExStoreDirectToNode);


    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
        "Storing [%s] (%p) directly into node [%s] (%p)"
        " with no implicit conversion\n",
        AcpiUtGetObjectTypeName (SourceDesc), SourceDesc,
        AcpiUtGetTypeName (Node->Type), Node));

    /* Copy the source object to a new object */

    Status = AcpiUtCopyIobjectToIobject (SourceDesc, &NewDesc, WalkState);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Attach the new object to the node */

    Status = AcpiNsAttachObject (Node, NewDesc, NewDesc->Common.Type);
    AcpiUtRemoveReference (NewDesc);
    return_ACPI_STATUS (Status);
}