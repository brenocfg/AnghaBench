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
typedef  int UINT32 ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_IO_ADDRESS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 scalar_t__ ACPI_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_UINT16_MAX ; 
 scalar_t__ AE_AML_ILLEGAL_ADDRESS ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AcpiGbl_TruncateIoAddresses ; 
 scalar_t__ AcpiHwValidateIoRequest (int /*<<< orphan*/ ,int) ; 
 scalar_t__ AcpiOsWritePort (int /*<<< orphan*/ ,int,int) ; 

ACPI_STATUS
AcpiHwWritePort (
    ACPI_IO_ADDRESS         Address,
    UINT32                  Value,
    UINT32                  Width)
{
    ACPI_STATUS             Status;
    UINT32                  i;


    /* Truncate address to 16 bits if requested */

    if (AcpiGbl_TruncateIoAddresses)
    {
        Address &= ACPI_UINT16_MAX;
    }

    /* Validate the entire request and perform the I/O */

    Status = AcpiHwValidateIoRequest (Address, Width);
    if (ACPI_SUCCESS (Status))
    {
        Status = AcpiOsWritePort (Address, Value, Width);
        return (Status);
    }

    if (Status != AE_AML_ILLEGAL_ADDRESS)
    {
        return (Status);
    }

    /*
     * There has been a protection violation within the request. Fall
     * back to byte granularity port I/O and ignore the failing bytes.
     * This provides compatibility with other ACPI implementations.
     */
    for (i = 0; i < Width; i += 8)
    {
        /* Validate and write one byte */

        if (AcpiHwValidateIoRequest (Address, 8) == AE_OK)
        {
            Status = AcpiOsWritePort (Address, (Value >> i) & 0xFF, 8);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }
        }

        Address++;
    }

    return (AE_OK);
}