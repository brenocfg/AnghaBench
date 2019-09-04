#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_10__ {size_t Count; int /*<<< orphan*/ * Elements; } ;
struct TYPE_13__ {TYPE_1__ Package; } ;
struct TYPE_11__ {size_t Count; int /*<<< orphan*/  Flags; TYPE_3__** Elements; } ;
struct TYPE_12__ {TYPE_2__ Package; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_4__ ACPI_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  AcpiUtCopyEobjectToIobject (int /*<<< orphan*/ *,TYPE_3__**) ; 
 TYPE_3__* AcpiUtCreatePackageObject (size_t) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_3__*) ; 
 int /*<<< orphan*/  UtCopyEpackageToIpackage ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiUtCopyEpackageToIpackage (
    ACPI_OBJECT             *ExternalObject,
    ACPI_OPERAND_OBJECT     **InternalObject)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_OPERAND_OBJECT     *PackageObject;
    ACPI_OPERAND_OBJECT     **PackageElements;
    UINT32                  i;


    ACPI_FUNCTION_TRACE (UtCopyEpackageToIpackage);


    /* Create the package object */

    PackageObject = AcpiUtCreatePackageObject (
        ExternalObject->Package.Count);
    if (!PackageObject)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    PackageElements = PackageObject->Package.Elements;

    /*
     * Recursive implementation. Probably ok, since nested external
     * packages as parameters should be very rare.
     */
    for (i = 0; i < ExternalObject->Package.Count; i++)
    {
        Status = AcpiUtCopyEobjectToIobject (
            &ExternalObject->Package.Elements[i],
            &PackageElements[i]);
        if (ACPI_FAILURE (Status))
        {
            /* Truncate package and delete it */

            PackageObject->Package.Count = i;
            PackageElements[i] = NULL;
            AcpiUtRemoveReference (PackageObject);
            return_ACPI_STATUS (Status);
        }
    }

    /* Mark package data valid */

    PackageObject->Package.Flags |= AOPOBJ_DATA_VALID;

    *InternalObject = PackageObject;
    return_ACPI_STATUS (Status);
}