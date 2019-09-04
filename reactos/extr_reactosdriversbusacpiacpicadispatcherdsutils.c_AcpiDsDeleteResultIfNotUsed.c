#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AcpiDsIsResultUsed (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiDsResultPop (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DsDeleteResultIfNotUsed ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiDsDeleteResultIfNotUsed (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_OPERAND_OBJECT     *ResultObj,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE_PTR (DsDeleteResultIfNotUsed, ResultObj);


    if (!Op)
    {
        ACPI_ERROR ((AE_INFO, "Null Op"));
        return_VOID;
    }

    if (!ResultObj)
    {
        return_VOID;
    }

    if (!AcpiDsIsResultUsed (Op, WalkState))
    {
        /* Must pop the result stack (ObjDesc should be equal to ResultObj) */

        Status = AcpiDsResultPop (&ObjDesc, WalkState);
        if (ACPI_SUCCESS (Status))
        {
            AcpiUtRemoveReference (ResultObj);
        }
    }

    return_VOID;
}