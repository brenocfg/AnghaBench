#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  Integer; } ;
struct TYPE_28__ {int /*<<< orphan*/  OwnerId; TYPE_1__ Name; } ;
struct TYPE_24__ {int /*<<< orphan*/  AmlLength; int /*<<< orphan*/  AmlStart; } ;
struct TYPE_27__ {TYPE_3__ Method; } ;
struct TYPE_23__ {TYPE_7__* Node; } ;
struct TYPE_26__ {TYPE_2__ Common; } ;
struct TYPE_25__ {int /*<<< orphan*/  DescendingCallback; } ;
typedef  TYPE_4__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_5__ ACPI_PARSE_OBJECT ;
typedef  TYPE_6__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_7__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_PARSE ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AML_METHOD_OP ; 
 TYPE_4__* AcpiDsCreateWalkState (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiDsDeleteWalkState (TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiDsDetectNamedOpcodes ; 
 int /*<<< orphan*/  AcpiDsInitAmlWalk (TYPE_4__*,TYPE_5__*,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* AcpiPsAllocOp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiPsDeleteParseTree (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiPsFreeOp (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiPsParseAml (TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiPsSetName (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtGetNodeName (TYPE_7__*) ; 
 int /*<<< orphan*/  DsAutoSerializeMethod ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiDsAutoSerializeMethod (
    ACPI_NAMESPACE_NODE     *Node,
    ACPI_OPERAND_OBJECT     *ObjDesc)
{
    ACPI_STATUS             Status;
    ACPI_PARSE_OBJECT       *Op = NULL;
    ACPI_WALK_STATE         *WalkState;


    ACPI_FUNCTION_TRACE_PTR (DsAutoSerializeMethod, Node);


    ACPI_DEBUG_PRINT ((ACPI_DB_PARSE,
        "Method auto-serialization parse [%4.4s] %p\n",
        AcpiUtGetNodeName (Node), Node));

    /* Create/Init a root op for the method parse tree */

    Op = AcpiPsAllocOp (AML_METHOD_OP, ObjDesc->Method.AmlStart);
    if (!Op)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    AcpiPsSetName (Op, Node->Name.Integer);
    Op->Common.Node = Node;

    /* Create and initialize a new walk state */

    WalkState = AcpiDsCreateWalkState (Node->OwnerId, NULL, NULL, NULL);
    if (!WalkState)
    {
        AcpiPsFreeOp (Op);
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    Status = AcpiDsInitAmlWalk (WalkState, Op, Node,
        ObjDesc->Method.AmlStart, ObjDesc->Method.AmlLength, NULL, 0);
    if (ACPI_FAILURE (Status))
    {
        AcpiDsDeleteWalkState (WalkState);
        AcpiPsFreeOp (Op);
        return_ACPI_STATUS (Status);
    }

    WalkState->DescendingCallback = AcpiDsDetectNamedOpcodes;

    /* Parse the method, scan for creation of named objects */

    Status = AcpiPsParseAml (WalkState);

    AcpiPsDeleteParseTree (Op);
    return_ACPI_STATUS (Status);
}