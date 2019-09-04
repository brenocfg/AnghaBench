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
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_READ ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiEvAddressSpaceDispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__*) ; 

__attribute__((used)) static ACPI_STATUS
AcpiExRegionRead (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    UINT32                  Length,
    UINT8                   *Buffer)
{
    ACPI_STATUS             Status;
    UINT64                  Value;
    UINT32                  RegionOffset = 0;
    UINT32                  i;


    /* Bytewise reads */

    for (i = 0; i < Length; i++)
    {
        Status = AcpiEvAddressSpaceDispatch (ObjDesc, NULL, ACPI_READ,
            RegionOffset, 8, &Value);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }

        *Buffer = (UINT8) Value;
        Buffer++;
        RegionOffset++;
    }

    return (AE_OK);
}