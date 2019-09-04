#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_28__ {int /*<<< orphan*/  Type; } ;
struct TYPE_27__ {int Class; int /*<<< orphan*/  ObjectType; } ;
struct TYPE_24__ {TYPE_9__* Node; } ;
struct TYPE_23__ {scalar_t__ AmlOpcode; } ;
struct TYPE_26__ {TYPE_5__ Named; TYPE_4__ Common; } ;
struct TYPE_25__ {scalar_t__ Opcode; int WalkType; TYPE_8__* OpInfo; TYPE_3__* ControlState; TYPE_7__* Origin; TYPE_7__* Op; } ;
struct TYPE_21__ {TYPE_7__* PredicateOp; } ;
struct TYPE_20__ {scalar_t__ State; } ;
struct TYPE_22__ {TYPE_2__ Control; TYPE_1__ Common; } ;
typedef  TYPE_6__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_7__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_CONTROL_CONDITIONAL_EXECUTING ; 
 scalar_t__ ACPI_CONTROL_PREDICATE_EXECUTING ; 
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int ACPI_WALK_METHOD ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_CLASS_CONTROL 131 
#define  AML_CLASS_CREATE 130 
#define  AML_CLASS_EXECUTE 129 
#define  AML_CLASS_NAMED_OBJECT 128 
 scalar_t__ AML_INT_NAMEPATH_OP ; 
 scalar_t__ AML_SCOPE_OP ; 
 int /*<<< orphan*/  AcpiDsExecBeginControlOp (TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  AcpiDsLoad2BeginOp (TYPE_6__*,TYPE_7__**) ; 
 int /*<<< orphan*/  AcpiDsMethodError (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiDsScopeStackPop (TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiDsScopeStackPush (TYPE_9__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 scalar_t__ AcpiNsOpensScope (int /*<<< orphan*/ ) ; 
 TYPE_8__* AcpiPsGetOpcodeInfo (scalar_t__) ; 
 int /*<<< orphan*/  AcpiUtGetTypeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DsExecBeginOp ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiDsExecBeginOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_PARSE_OBJECT       **OutOp)
{
    ACPI_PARSE_OBJECT       *Op;
    ACPI_STATUS             Status = AE_OK;
    UINT32                  OpcodeClass;


    ACPI_FUNCTION_TRACE_PTR (DsExecBeginOp, WalkState);


    Op = WalkState->Op;
    if (!Op)
    {
        Status = AcpiDsLoad2BeginOp (WalkState, OutOp);
        if (ACPI_FAILURE (Status))
        {
            goto ErrorExit;
        }

        Op = *OutOp;
        WalkState->Op = Op;
        WalkState->Opcode = Op->Common.AmlOpcode;
        WalkState->OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);

        if (AcpiNsOpensScope (WalkState->OpInfo->ObjectType))
        {
            ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH,
                "(%s) Popping scope for Op %p\n",
                AcpiUtGetTypeName (WalkState->OpInfo->ObjectType), Op));

            Status = AcpiDsScopeStackPop (WalkState);
            if (ACPI_FAILURE (Status))
            {
                goto ErrorExit;
            }
        }
    }

    if (Op == WalkState->Origin)
    {
        if (OutOp)
        {
            *OutOp = Op;
        }

        return_ACPI_STATUS (AE_OK);
    }

    /*
     * If the previous opcode was a conditional, this opcode
     * must be the beginning of the associated predicate.
     * Save this knowledge in the current scope descriptor
     */
    if ((WalkState->ControlState) &&
        (WalkState->ControlState->Common.State ==
            ACPI_CONTROL_CONDITIONAL_EXECUTING))
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
            "Exec predicate Op=%p State=%p\n",
            Op, WalkState));

        WalkState->ControlState->Common.State =
            ACPI_CONTROL_PREDICATE_EXECUTING;

        /* Save start of predicate */

        WalkState->ControlState->Control.PredicateOp = Op;
    }


    OpcodeClass = WalkState->OpInfo->Class;

    /* We want to send namepaths to the load code */

    if (Op->Common.AmlOpcode == AML_INT_NAMEPATH_OP)
    {
        OpcodeClass = AML_CLASS_NAMED_OBJECT;
    }

    /*
     * Handle the opcode based upon the opcode type
     */
    switch (OpcodeClass)
    {
    case AML_CLASS_CONTROL:

        Status = AcpiDsExecBeginControlOp (WalkState, Op);
        break;

    case AML_CLASS_NAMED_OBJECT:

        if (WalkState->WalkType & ACPI_WALK_METHOD)
        {
            /*
             * Found a named object declaration during method execution;
             * we must enter this object into the namespace. The created
             * object is temporary and will be deleted upon completion of
             * the execution of this method.
             *
             * Note 10/2010: Except for the Scope() op. This opcode does
             * not actually create a new object, it refers to an existing
             * object. However, for Scope(), we want to indeed open a
             * new scope.
             */
            if (Op->Common.AmlOpcode != AML_SCOPE_OP)
            {
                Status = AcpiDsLoad2BeginOp (WalkState, NULL);
            }
            else
            {
                Status = AcpiDsScopeStackPush (
                    Op->Named.Node, Op->Named.Node->Type, WalkState);
                if (ACPI_FAILURE (Status))
                {
                    return_ACPI_STATUS (Status);
                }
            }
        }
        break;

    case AML_CLASS_EXECUTE:
    case AML_CLASS_CREATE:

        break;

    default:

        break;
    }

    /* Nothing to do here during method execution */

    return_ACPI_STATUS (Status);


ErrorExit:
    Status = AcpiDsMethodError (Status, WalkState);
    return_ACPI_STATUS (Status);
}