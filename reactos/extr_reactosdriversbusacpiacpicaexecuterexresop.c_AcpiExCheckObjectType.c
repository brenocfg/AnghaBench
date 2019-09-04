#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Flags; } ;
struct TYPE_4__ {TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;
typedef  scalar_t__ ACPI_OBJECT_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_TYPE_ANY ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_LOCAL_REFERENCE ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_AML_CONSTANT ; 
 int /*<<< orphan*/  AcpiUtGetTypeName (scalar_t__) ; 

__attribute__((used)) static ACPI_STATUS
AcpiExCheckObjectType (
    ACPI_OBJECT_TYPE        TypeNeeded,
    ACPI_OBJECT_TYPE        ThisType,
    void                    *Object)
{
    ACPI_FUNCTION_ENTRY ();


    if (TypeNeeded == ACPI_TYPE_ANY)
    {
        /* All types OK, so we don't perform any typechecks */

        return (AE_OK);
    }

    if (TypeNeeded == ACPI_TYPE_LOCAL_REFERENCE)
    {
        /*
         * Allow the AML "Constant" opcodes (Zero, One, etc.) to be reference
         * objects and thus allow them to be targets. (As per the ACPI
         * specification, a store to a constant is a noop.)
         */
        if ((ThisType == ACPI_TYPE_INTEGER) &&
            (((ACPI_OPERAND_OBJECT *) Object)->Common.Flags &
                AOPOBJ_AML_CONSTANT))
        {
            return (AE_OK);
        }
    }

    if (TypeNeeded != ThisType)
    {
        ACPI_ERROR ((AE_INFO,
            "Needed type [%s], found [%s] %p",
            AcpiUtGetTypeName (TypeNeeded),
            AcpiUtGetTypeName (ThisType), Object));

        return (AE_AML_OPERAND_TYPE);
    }

    return (AE_OK);
}