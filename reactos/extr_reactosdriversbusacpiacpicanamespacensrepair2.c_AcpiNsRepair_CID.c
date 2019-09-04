#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_7__ {scalar_t__ Type; int /*<<< orphan*/  ReferenceCount; } ;
struct TYPE_6__ {scalar_t__ Count; TYPE_3__** Elements; } ;
struct TYPE_8__ {TYPE_2__ Common; TYPE_1__ Package; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_EVALUATE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 scalar_t__ ACPI_TYPE_STRING ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiNsRepair_HID (int /*<<< orphan*/ *,TYPE_3__**) ; 

__attribute__((used)) static ACPI_STATUS
AcpiNsRepair_CID (
    ACPI_EVALUATE_INFO      *Info,
    ACPI_OPERAND_OBJECT     **ReturnObjectPtr)
{
    ACPI_STATUS             Status;
    ACPI_OPERAND_OBJECT     *ReturnObject = *ReturnObjectPtr;
    ACPI_OPERAND_OBJECT     **ElementPtr;
    ACPI_OPERAND_OBJECT     *OriginalElement;
    UINT16                  OriginalRefCount;
    UINT32                  i;


    /* Check for _CID as a simple string */

    if (ReturnObject->Common.Type == ACPI_TYPE_STRING)
    {
        Status = AcpiNsRepair_HID (Info, ReturnObjectPtr);
        return (Status);
    }

    /* Exit if not a Package */

    if (ReturnObject->Common.Type != ACPI_TYPE_PACKAGE)
    {
        return (AE_OK);
    }

    /* Examine each element of the _CID package */

    ElementPtr = ReturnObject->Package.Elements;
    for (i = 0; i < ReturnObject->Package.Count; i++)
    {
        OriginalElement = *ElementPtr;
        OriginalRefCount = OriginalElement->Common.ReferenceCount;

        Status = AcpiNsRepair_HID (Info, ElementPtr);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }

        if (OriginalElement != *ElementPtr)
        {
            /* Update reference count of new object */

            (*ElementPtr)->Common.ReferenceCount =
                OriginalRefCount;
        }

        ElementPtr++;
    }

    return (AE_OK);
}