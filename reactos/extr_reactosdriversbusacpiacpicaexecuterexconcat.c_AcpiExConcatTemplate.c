#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
struct TYPE_8__ {int* Pointer; } ;
struct TYPE_9__ {TYPE_1__ Buffer; } ;
typedef  int /*<<< orphan*/  AML_RESOURCE_END_TAG ;
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int ACPI_SIZE ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_PTR_DIFF (int*,int*) ; 
 int ACPI_RESOURCE_NAME_END_TAG ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_2__* AcpiUtCreateBufferObject (int) ; 
 int /*<<< orphan*/  AcpiUtGetResourceEndTag (TYPE_2__*,int**) ; 
 int /*<<< orphan*/  ExConcatTemplate ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiExConcatTemplate (
    ACPI_OPERAND_OBJECT     *Operand0,
    ACPI_OPERAND_OBJECT     *Operand1,
    ACPI_OPERAND_OBJECT     **ActualReturnDesc,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status;
    ACPI_OPERAND_OBJECT     *ReturnDesc;
    UINT8                   *NewBuf;
    UINT8                   *EndTag;
    ACPI_SIZE               Length0;
    ACPI_SIZE               Length1;
    ACPI_SIZE               NewLength;


    ACPI_FUNCTION_TRACE (ExConcatTemplate);


    /*
     * Find the EndTag descriptor in each resource template.
     * Note1: returned pointers point TO the EndTag, not past it.
     * Note2: zero-length buffers are allowed; treated like one EndTag
     */

    /* Get the length of the first resource template */

    Status = AcpiUtGetResourceEndTag (Operand0, &EndTag);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    Length0 = ACPI_PTR_DIFF (EndTag, Operand0->Buffer.Pointer);

    /* Get the length of the second resource template */

    Status = AcpiUtGetResourceEndTag (Operand1, &EndTag);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    Length1 = ACPI_PTR_DIFF (EndTag, Operand1->Buffer.Pointer);

    /* Combine both lengths, minimum size will be 2 for EndTag */

    NewLength = Length0 + Length1 + sizeof (AML_RESOURCE_END_TAG);

    /* Create a new buffer object for the result (with one EndTag) */

    ReturnDesc = AcpiUtCreateBufferObject (NewLength);
    if (!ReturnDesc)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /*
     * Copy the templates to the new buffer, 0 first, then 1 follows. One
     * EndTag descriptor is copied from Operand1.
     */
    NewBuf = ReturnDesc->Buffer.Pointer;
    memcpy (NewBuf, Operand0->Buffer.Pointer, Length0);
    memcpy (NewBuf + Length0, Operand1->Buffer.Pointer, Length1);

    /* Insert EndTag and set the checksum to zero, means "ignore checksum" */

    NewBuf[NewLength - 1] = 0;
    NewBuf[NewLength - 2] = ACPI_RESOURCE_NAME_END_TAG | 1;

    /* Return the completed resource template */

    *ActualReturnDesc = ReturnDesc;
    return_ACPI_STATUS (AE_OK);
}