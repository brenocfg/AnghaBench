#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_10__ {TYPE_4__** ThisTargetObj; } ;
struct TYPE_13__ {TYPE_2__ Pkg; } ;
struct TYPE_9__ {int /*<<< orphan*/  Flags; } ;
struct TYPE_11__ {scalar_t__ Type; } ;
struct TYPE_12__ {TYPE_1__ Package; TYPE_3__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_5__ ACPI_GENERIC_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_LOCAL_REFERENCE ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  AcpiDsResolvePackageElement (TYPE_4__**) ; 
 int /*<<< orphan*/  DsInitPackageElement ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiDsInitPackageElement (
    UINT8                   ObjectType,
    ACPI_OPERAND_OBJECT     *SourceObject,
    ACPI_GENERIC_STATE      *State,
    void                    *Context)
{
    ACPI_OPERAND_OBJECT     **ElementPtr;


    ACPI_FUNCTION_TRACE (DsInitPackageElement);


    if (!SourceObject)
    {
        return_ACPI_STATUS (AE_OK);
    }

    /*
     * The following code is a bit of a hack to workaround a (current)
     * limitation of the ACPI_PKG_CALLBACK interface. We need a pointer
     * to the location within the element array because a new object
     * may be created and stored there.
     */
    if (Context)
    {
        /* A direct call was made to this function */

        ElementPtr = (ACPI_OPERAND_OBJECT **) Context;
    }
    else
    {
        /* Call came from AcpiUtWalkPackageTree */

        ElementPtr = State->Pkg.ThisTargetObj;
    }

    /* We are only interested in reference objects/elements */

    if (SourceObject->Common.Type == ACPI_TYPE_LOCAL_REFERENCE)
    {
        /* Attempt to resolve the (named) reference to a namespace node */

        AcpiDsResolvePackageElement (ElementPtr);
    }
    else if (SourceObject->Common.Type == ACPI_TYPE_PACKAGE)
    {
        SourceObject->Package.Flags |= AOPOBJ_DATA_VALID;
    }

    return_ACPI_STATUS (AE_OK);
}