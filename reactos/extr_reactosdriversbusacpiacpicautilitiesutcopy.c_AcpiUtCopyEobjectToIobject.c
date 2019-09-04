#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ Type; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;
typedef  TYPE_1__ ACPI_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  AcpiUtCopyEpackageToIpackage (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  AcpiUtCopyEsimpleToIsimple (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  UtCopyEobjectToIobject ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiUtCopyEobjectToIobject (
    ACPI_OBJECT             *ExternalObject,
    ACPI_OPERAND_OBJECT     **InternalObject)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (UtCopyEobjectToIobject);


    if (ExternalObject->Type == ACPI_TYPE_PACKAGE)
    {
        Status = AcpiUtCopyEpackageToIpackage (
            ExternalObject, InternalObject);
    }
    else
    {
        /*
         * Build a simple object (no nested objects)
         */
        Status = AcpiUtCopyEsimpleToIsimple (ExternalObject,
            InternalObject);
    }

    return_ACPI_STATUS (Status);
}