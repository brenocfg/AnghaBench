#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_11__ {int /*<<< orphan*/  String; } ;
struct TYPE_12__ {TYPE_4__* Parent; TYPE_4__* Next; TYPE_2__ Value; int /*<<< orphan*/  AmlOpcode; } ;
struct TYPE_10__ {scalar_t__ AmlOpcode; } ;
struct TYPE_13__ {TYPE_3__ Common; TYPE_1__ Named; } ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_PARSE_TREES ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ ACPI_IS_DEBUG_ENABLED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_LV_PARSE_TREES ; 
 scalar_t__ AML_INT_NAMEPATH_OP ; 
 scalar_t__ AML_STRING_OP ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  AcpiPsFreeOp (TYPE_4__*) ; 
 TYPE_4__* AcpiPsGetArg (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiPsGetOpcodeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PsDeleteParseTree ; 
 int /*<<< orphan*/  _COMPONENT ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiPsDeleteParseTree (
    ACPI_PARSE_OBJECT       *SubtreeRoot)
{
    ACPI_PARSE_OBJECT       *Op = SubtreeRoot;
    ACPI_PARSE_OBJECT       *Next = NULL;
    ACPI_PARSE_OBJECT       *Parent = NULL;
    UINT32                  Level = 0;


    ACPI_FUNCTION_TRACE_PTR (PsDeleteParseTree, SubtreeRoot);

    ACPI_DEBUG_PRINT ((ACPI_DB_PARSE_TREES,
        " root %p\n", SubtreeRoot));

    /* Visit all nodes in the subtree */

    while (Op)
    {
        if (Op != Parent)
        {
            /* This is the descending case */

            if (ACPI_IS_DEBUG_ENABLED (ACPI_LV_PARSE_TREES, _COMPONENT))
            {
                /* This debug option will print the entire parse tree */

                AcpiOsPrintf ("        %*.s%s %p", (Level * 4), " ",
                    AcpiPsGetOpcodeName (Op->Common.AmlOpcode), Op);

                if (Op->Named.AmlOpcode == AML_INT_NAMEPATH_OP)
                {
                    AcpiOsPrintf ("    %4.4s", Op->Common.Value.String);
                }
                if (Op->Named.AmlOpcode == AML_STRING_OP)
                {
                    AcpiOsPrintf ("    %s", Op->Common.Value.String);
                }
                AcpiOsPrintf ("\n");
            }

            /* Look for an argument or child of the current op */

            Next = AcpiPsGetArg (Op, 0);
            if (Next)
            {
                /* Still going downward in tree (Op is not completed yet) */

                Op = Next;
                Level++;
                continue;
            }
        }

        /* No more children, this Op is complete. */

        Next = Op->Common.Next;
        Parent = Op->Common.Parent;

        AcpiPsFreeOp (Op);

        /* If we are back to the starting point, the walk is complete. */

        if (Op == SubtreeRoot)
        {
            return_VOID;
        }

        if (Next)
        {
            Op = Next;
        }
        else
        {
            Level--;
            Op = Parent;
        }
    }

    return_VOID;
}