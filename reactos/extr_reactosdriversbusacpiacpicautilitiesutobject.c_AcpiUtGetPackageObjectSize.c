#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Length; int NumPackages; scalar_t__ ObjectSpace; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int ACPI_SIZE ;
typedef  TYPE_1__ ACPI_PKG_INFO ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ACPI_ROUND_UP_TO_NATIVE_WORD (int) ; 
 int /*<<< orphan*/  AcpiUtGetElementLength ; 
 int /*<<< orphan*/  AcpiUtWalkPackageTree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  UtGetPackageObjectSize ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiUtGetPackageObjectSize (
    ACPI_OPERAND_OBJECT     *InternalObject,
    ACPI_SIZE               *ObjLength)
{
    ACPI_STATUS             Status;
    ACPI_PKG_INFO           Info;


    ACPI_FUNCTION_TRACE_PTR (UtGetPackageObjectSize, InternalObject);


    Info.Length = 0;
    Info.ObjectSpace = 0;
    Info.NumPackages = 1;

    Status = AcpiUtWalkPackageTree (
        InternalObject, NULL, AcpiUtGetElementLength, &Info);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /*
     * We have handled all of the objects in all levels of the package.
     * just add the length of the package objects themselves.
     * Round up to the next machine word.
     */
    Info.Length += ACPI_ROUND_UP_TO_NATIVE_WORD (
        sizeof (ACPI_OBJECT)) * (ACPI_SIZE) Info.NumPackages;

    /* Return the total package length */

    *ObjLength = Info.Length;
    return_ACPI_STATUS (Status);
}