#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  Node; TYPE_2__* ObjDesc; int /*<<< orphan*/  FullPathname; int /*<<< orphan*/  PassNumber; } ;
struct TYPE_14__ {int /*<<< orphan*/  ParseFlags; int /*<<< orphan*/  MethodIsNested; int /*<<< orphan*/  MethodPathname; } ;
struct TYPE_12__ {int InfoFlags; int /*<<< orphan*/  AmlLength; int /*<<< orphan*/  AmlStart; int /*<<< orphan*/  OwnerId; } ;
struct TYPE_13__ {TYPE_1__ Method; } ;
typedef  TYPE_3__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;
typedef  TYPE_4__ ACPI_EVALUATE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_METHOD_MODULE_LEVEL ; 
 int /*<<< orphan*/  ACPI_PARSE_MODULE_LEVEL ; 
 int /*<<< orphan*/  ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 TYPE_3__* AcpiDsCreateWalkState (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiDsDeleteWalkState (TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiDsInitAmlWalk (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDsScopeStackPush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiExEnterInterpreter () ; 
 int /*<<< orphan*/  AcpiExExitInterpreter () ; 
 int /*<<< orphan*/  AcpiGbl_RootNode ; 
 int /*<<< orphan*/ * AcpiPsCreateScopeOp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiPsDeleteParseTree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiPsParseAml (TYPE_3__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PsExecuteTable ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiPsExecuteTable (
    ACPI_EVALUATE_INFO      *Info)
{
    ACPI_STATUS             Status;
    ACPI_PARSE_OBJECT       *Op = NULL;
    ACPI_WALK_STATE         *WalkState = NULL;


    ACPI_FUNCTION_TRACE (PsExecuteTable);


    /* Create and init a Root Node */

    Op = AcpiPsCreateScopeOp (Info->ObjDesc->Method.AmlStart);
    if (!Op)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }

    /* Create and initialize a new walk state */

    WalkState = AcpiDsCreateWalkState (
        Info->ObjDesc->Method.OwnerId, NULL, NULL, NULL);
    if (!WalkState)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }

    Status = AcpiDsInitAmlWalk (WalkState, Op, Info->Node,
        Info->ObjDesc->Method.AmlStart,
        Info->ObjDesc->Method.AmlLength, Info, Info->PassNumber);
    if (ACPI_FAILURE (Status))
    {
        goto Cleanup;
    }

    WalkState->MethodPathname = Info->FullPathname;
    WalkState->MethodIsNested = FALSE;

    if (Info->ObjDesc->Method.InfoFlags & ACPI_METHOD_MODULE_LEVEL)
    {
        WalkState->ParseFlags |= ACPI_PARSE_MODULE_LEVEL;
    }

    /* Info->Node is the default location to load the table  */

    if (Info->Node && Info->Node != AcpiGbl_RootNode)
    {
        Status = AcpiDsScopeStackPush (
            Info->Node, ACPI_TYPE_METHOD, WalkState);
        if (ACPI_FAILURE (Status))
        {
            goto Cleanup;
        }
    }

    /*
     * Parse the AML, WalkState will be deleted by ParseAml
     */
    AcpiExEnterInterpreter ();
    Status = AcpiPsParseAml (WalkState);
    AcpiExExitInterpreter ();
    WalkState = NULL;

Cleanup:
    if (WalkState)
    {
        AcpiDsDeleteWalkState (WalkState);
    }
    if (Op)
    {
        AcpiPsDeleteParseTree (Op);
    }
    return_ACPI_STATUS (Status);
}