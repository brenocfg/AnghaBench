#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_22__ {int ReturnFlags; TYPE_4__* ParentPackage; TYPE_3__* Predefined; } ;
struct TYPE_21__ {int /*<<< orphan*/  Flags; } ;
struct TYPE_18__ {scalar_t__ Type; } ;
struct TYPE_20__ {TYPE_2__ Common; } ;
struct TYPE_17__ {scalar_t__ ExpectedBtypes; } ;
struct TYPE_19__ {TYPE_1__ Info; } ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  TYPE_3__ ACPI_PREDEFINED_INFO ;
typedef  TYPE_4__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_5__ ACPI_NAMESPACE_NODE ;
typedef  TYPE_6__ ACPI_EVALUATE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_NOT_PACKAGE_ELEMENT ; 
 int ACPI_OBJECT_REPAIRED ; 
 scalar_t__ ACPI_RTYPE_ALL ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 scalar_t__ AE_AML_OPERAND_TYPE ; 
 scalar_t__ AE_AML_OPERAND_VALUE ; 
 scalar_t__ AE_CTRL_RETURN_VALUE ; 
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  ANOBJ_EVALUATED ; 
 scalar_t__ AcpiGbl_DisableAutoRepair ; 
 scalar_t__ AcpiNsCheckObjectType (TYPE_6__*,TYPE_4__**,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ AcpiNsCheckPackage (TYPE_6__*,TYPE_4__**) ; 
 scalar_t__ AcpiNsComplexRepairs (TYPE_6__*,TYPE_5__*,scalar_t__,TYPE_4__**) ; 

ACPI_STATUS
AcpiNsCheckReturnValue (
    ACPI_NAMESPACE_NODE         *Node,
    ACPI_EVALUATE_INFO          *Info,
    UINT32                      UserParamCount,
    ACPI_STATUS                 ReturnStatus,
    ACPI_OPERAND_OBJECT         **ReturnObjectPtr)
{
    ACPI_STATUS                 Status;
    const ACPI_PREDEFINED_INFO  *Predefined;


    /* If not a predefined name, we cannot validate the return object */

    Predefined = Info->Predefined;
    if (!Predefined)
    {
        return (AE_OK);
    }

    /*
     * If the method failed or did not actually return an object, we cannot
     * validate the return object
     */
    if ((ReturnStatus != AE_OK) &&
        (ReturnStatus != AE_CTRL_RETURN_VALUE))
    {
        return (AE_OK);
    }

    /*
     * Return value validation and possible repair.
     *
     * 1) Don't perform return value validation/repair if this feature
     * has been disabled via a global option.
     *
     * 2) We have a return value, but if one wasn't expected, just exit,
     * this is not a problem. For example, if the "Implicit Return"
     * feature is enabled, methods will always return a value.
     *
     * 3) If the return value can be of any type, then we cannot perform
     * any validation, just exit.
     */
    if (AcpiGbl_DisableAutoRepair ||
        (!Predefined->Info.ExpectedBtypes) ||
        (Predefined->Info.ExpectedBtypes == ACPI_RTYPE_ALL))
    {
        return (AE_OK);
    }

    /*
     * Check that the type of the main return object is what is expected
     * for this predefined name
     */
    Status = AcpiNsCheckObjectType (Info, ReturnObjectPtr,
        Predefined->Info.ExpectedBtypes, ACPI_NOT_PACKAGE_ELEMENT);
    if (ACPI_FAILURE (Status))
    {
        goto Exit;
    }

    /*
     *
     * 4) If there is no return value and it is optional, just return
     * AE_OK (_WAK).
     */
    if (!(*ReturnObjectPtr))
    {
        goto Exit;
    }

    /*
     * For returned Package objects, check the type of all sub-objects.
     * Note: Package may have been newly created by call above.
     */
    if ((*ReturnObjectPtr)->Common.Type == ACPI_TYPE_PACKAGE)
    {
        Info->ParentPackage = *ReturnObjectPtr;
        Status = AcpiNsCheckPackage (Info, ReturnObjectPtr);
        if (ACPI_FAILURE (Status))
        {
            /* We might be able to fix some errors */

            if ((Status != AE_AML_OPERAND_TYPE) &&
                (Status != AE_AML_OPERAND_VALUE))
            {
                goto Exit;
            }
        }
    }

    /*
     * The return object was OK, or it was successfully repaired above.
     * Now make some additional checks such as verifying that package
     * objects are sorted correctly (if required) or buffer objects have
     * the correct data width (bytes vs. dwords). These repairs are
     * performed on a per-name basis, i.e., the code is specific to
     * particular predefined names.
     */
    Status = AcpiNsComplexRepairs (Info, Node, Status, ReturnObjectPtr);

Exit:
    /*
     * If the object validation failed or if we successfully repaired one
     * or more objects, mark the parent node to suppress further warning
     * messages during the next evaluation of the same method/object.
     */
    if (ACPI_FAILURE (Status) ||
       (Info->ReturnFlags & ACPI_OBJECT_REPAIRED))
    {
        Node->Flags |= ANOBJ_EVALUATED;
    }

    return (Status);
}