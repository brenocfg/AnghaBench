#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_EVALUATE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiNsCheckObjectType (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static ACPI_STATUS
AcpiNsCheckPackageElements (
    ACPI_EVALUATE_INFO          *Info,
    ACPI_OPERAND_OBJECT         **Elements,
    UINT8                       Type1,
    UINT32                      Count1,
    UINT8                       Type2,
    UINT32                      Count2,
    UINT32                      StartIndex)
{
    ACPI_OPERAND_OBJECT         **ThisElement = Elements;
    ACPI_STATUS                 Status;
    UINT32                      i;


    /*
     * Up to two groups of package elements are supported by the data
     * structure. All elements in each group must be of the same type.
     * The second group can have a count of zero.
     */
    for (i = 0; i < Count1; i++)
    {
        Status = AcpiNsCheckObjectType (Info, ThisElement,
            Type1, i + StartIndex);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }

        ThisElement++;
    }

    for (i = 0; i < Count2; i++)
    {
        Status = AcpiNsCheckObjectType (Info, ThisElement,
            Type2, (i + Count1 + StartIndex));
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }

        ThisElement++;
    }

    return (AE_OK);
}