#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ReferenceCount; } ;
struct TYPE_8__ {TYPE_1__ Common; } ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_ALLOCATIONS ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_DESC_TYPE_NAMED ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (TYPE_2__*) ; 
 int /*<<< orphan*/  ACPI_GET_FUNCTION_NAME ; 
 int /*<<< orphan*/  AcpiUtUpdateObjectReference (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtValidInternalObject (TYPE_2__*) ; 
 int /*<<< orphan*/  REF_DECREMENT ; 
 int /*<<< orphan*/  UtRemoveReference ; 

void
AcpiUtRemoveReference (
    ACPI_OPERAND_OBJECT     *Object)
{

    ACPI_FUNCTION_NAME (UtRemoveReference);


    /*
     * Allow a NULL pointer to be passed in, just ignore it. This saves
     * each caller from having to check. Also, ignore NS nodes.
     */
    if (!Object ||
        (ACPI_GET_DESCRIPTOR_TYPE (Object) == ACPI_DESC_TYPE_NAMED))

    {
        return;
    }

    /* Ensure that we have a valid object */

    if (!AcpiUtValidInternalObject (Object))
    {
        return;
    }

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_ALLOCATIONS,
        "%s: Obj %p Current Refs=%X [To Be Decremented]\n",
        ACPI_GET_FUNCTION_NAME, Object, Object->Common.ReferenceCount));

    /*
     * Decrement the reference count, and only actually delete the object
     * if the reference count becomes 0. (Must also decrement the ref count
     * of all subobjects!)
     */
    (void) AcpiUtUpdateObjectReference (Object, REF_DECREMENT);
    return;
}