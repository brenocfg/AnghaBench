#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT64 ;
struct TYPE_6__ {int /*<<< orphan*/  Value; } ;
struct TYPE_7__ {TYPE_1__ Integer; } ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 TYPE_2__* AcpiUtCreateInternalObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UtCreateIntegerObject ; 
 int /*<<< orphan*/  return_PTR (TYPE_2__*) ; 

ACPI_OPERAND_OBJECT *
AcpiUtCreateIntegerObject (
    UINT64                  InitialValue)
{
    ACPI_OPERAND_OBJECT     *IntegerDesc;


    ACPI_FUNCTION_TRACE (UtCreateIntegerObject);


    /* Create and initialize a new integer object */

    IntegerDesc = AcpiUtCreateInternalObject (ACPI_TYPE_INTEGER);
    if (!IntegerDesc)
    {
        return_PTR (NULL);
    }

    IntegerDesc->Integer.Value = InitialValue;
    return_PTR (IntegerDesc);
}