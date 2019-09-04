#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_10__ {scalar_t__ Value; int /*<<< orphan*/  DescriptorType; } ;
struct TYPE_9__ {int /*<<< orphan*/ * Node; } ;
struct TYPE_12__ {TYPE_2__ Common; TYPE_1__ Scope; } ;
struct TYPE_11__ {TYPE_4__* ScopeInfo; scalar_t__ ScopeDepth; } ;
typedef  TYPE_3__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  scalar_t__ ACPI_OBJECT_TYPE ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;
typedef  TYPE_4__ ACPI_GENERIC_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DESC_TYPE_STATE_WSCOPE ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_NAMESPACE_ROOT ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_4__* AcpiUtCreateGenericState () ; 
 int /*<<< orphan*/  AcpiUtGetNodeName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtGetTypeName (scalar_t__) ; 
 int /*<<< orphan*/  AcpiUtPushGenericState (TYPE_4__**,TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiUtValidObjectType (scalar_t__) ; 
 int /*<<< orphan*/  DsScopeStackPush ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiDsScopeStackPush (
    ACPI_NAMESPACE_NODE     *Node,
    ACPI_OBJECT_TYPE        Type,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_GENERIC_STATE      *ScopeInfo;
    ACPI_GENERIC_STATE      *OldScopeInfo;


    ACPI_FUNCTION_TRACE (DsScopeStackPush);


    if (!Node)
    {
        /* Invalid scope   */

        ACPI_ERROR ((AE_INFO, "Null scope parameter"));
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Make sure object type is valid */

    if (!AcpiUtValidObjectType (Type))
    {
        ACPI_WARNING ((AE_INFO,
            "Invalid object type: 0x%X", Type));
    }

    /* Allocate a new scope object */

    ScopeInfo = AcpiUtCreateGenericState ();
    if (!ScopeInfo)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Init new scope object */

    ScopeInfo->Common.DescriptorType = ACPI_DESC_TYPE_STATE_WSCOPE;
    ScopeInfo->Scope.Node = Node;
    ScopeInfo->Common.Value = (UINT16) Type;

    WalkState->ScopeDepth++;

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
        "[%.2d] Pushed scope ", (UINT32) WalkState->ScopeDepth));

    OldScopeInfo = WalkState->ScopeInfo;
    if (OldScopeInfo)
    {
        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_EXEC,
            "[%4.4s] (%s)",
            AcpiUtGetNodeName (OldScopeInfo->Scope.Node),
            AcpiUtGetTypeName (OldScopeInfo->Common.Value)));
    }
    else
    {
        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_EXEC, ACPI_NAMESPACE_ROOT));
    }

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_EXEC,
        ", New scope -> [%4.4s] (%s)\n",
        AcpiUtGetNodeName (ScopeInfo->Scope.Node),
        AcpiUtGetTypeName (ScopeInfo->Common.Value)));

    /* Push new scope object onto stack */

    AcpiUtPushGenericState (&WalkState->ScopeInfo, ScopeInfo);
    return_ACPI_STATUS (AE_OK);
}