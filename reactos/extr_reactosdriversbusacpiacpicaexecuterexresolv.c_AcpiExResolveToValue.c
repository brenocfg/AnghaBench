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
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CAST_INDIRECT_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_DESC_TYPE_NAMED ; 
 scalar_t__ ACPI_DESC_TYPE_OPERAND ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_NAMESPACE_NODE ; 
 int /*<<< orphan*/  AE_AML_NO_OPERAND ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiExResolveNodeToValue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiExResolveObjectToValue (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExResolveToValue ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiExResolveToValue (
    ACPI_OPERAND_OBJECT     **StackPtr,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE_PTR (ExResolveToValue, StackPtr);


    if (!StackPtr || !*StackPtr)
    {
        ACPI_ERROR ((AE_INFO, "Internal - null pointer"));
        return_ACPI_STATUS (AE_AML_NO_OPERAND);
    }

    /*
     * The entity pointed to by the StackPtr can be either
     * 1) A valid ACPI_OPERAND_OBJECT, or
     * 2) A ACPI_NAMESPACE_NODE (NamedObj)
     */
    if (ACPI_GET_DESCRIPTOR_TYPE (*StackPtr) == ACPI_DESC_TYPE_OPERAND)
    {
        Status = AcpiExResolveObjectToValue (StackPtr, WalkState);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }

        if (!*StackPtr)
        {
            ACPI_ERROR ((AE_INFO, "Internal - null pointer"));
            return_ACPI_STATUS (AE_AML_NO_OPERAND);
        }
    }

    /*
     * Object on the stack may have changed if AcpiExResolveObjectToValue()
     * was called (i.e., we can't use an _else_ here.)
     */
    if (ACPI_GET_DESCRIPTOR_TYPE (*StackPtr) == ACPI_DESC_TYPE_NAMED)
    {
        Status = AcpiExResolveNodeToValue (
            ACPI_CAST_INDIRECT_PTR (ACPI_NAMESPACE_NODE, StackPtr),
            WalkState);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC, "Resolved object %p\n", *StackPtr));
    return_ACPI_STATUS (AE_OK);
}