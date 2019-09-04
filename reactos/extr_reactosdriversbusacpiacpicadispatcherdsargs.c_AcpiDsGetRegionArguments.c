#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int Flags; int /*<<< orphan*/  Length; int /*<<< orphan*/  Address; int /*<<< orphan*/  SpaceId; int /*<<< orphan*/ * Node; } ;
struct TYPE_8__ {int /*<<< orphan*/  AmlStart; int /*<<< orphan*/  AmlLength; int /*<<< orphan*/  ScopeNode; } ;
struct TYPE_10__ {TYPE_2__ Region; TYPE_1__ Extra; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_EXEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ACPI_TYPE_REGION ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  AcpiDsExecuteArguments (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* AcpiNsGetSecondaryObject (TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiUtAddAddressRange (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtDisplayInitPathname (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtGetNodeName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DsGetRegionArguments ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiDsGetRegionArguments (
    ACPI_OPERAND_OBJECT     *ObjDesc)
{
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_STATUS             Status;
    ACPI_OPERAND_OBJECT     *ExtraDesc;


    ACPI_FUNCTION_TRACE_PTR (DsGetRegionArguments, ObjDesc);


    if (ObjDesc->Region.Flags & AOPOBJ_DATA_VALID)
    {
        return_ACPI_STATUS (AE_OK);
    }

    ExtraDesc = AcpiNsGetSecondaryObject (ObjDesc);
    if (!ExtraDesc)
    {
        return_ACPI_STATUS (AE_NOT_EXIST);
    }

    /* Get the Region node */

    Node = ObjDesc->Region.Node;

    ACPI_DEBUG_EXEC (AcpiUtDisplayInitPathname (
        ACPI_TYPE_REGION, Node, NULL));

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
        "[%4.4s] OpRegion Arg Init at AML %p\n",
        AcpiUtGetNodeName (Node), ExtraDesc->Extra.AmlStart));

    /* Execute the argument AML */

    Status = AcpiDsExecuteArguments (Node, ExtraDesc->Extra.ScopeNode,
        ExtraDesc->Extra.AmlLength, ExtraDesc->Extra.AmlStart);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    Status = AcpiUtAddAddressRange (ObjDesc->Region.SpaceId,
        ObjDesc->Region.Address, ObjDesc->Region.Length, Node);
    return_ACPI_STATUS (Status);
}