#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int UINT32 ;
struct TYPE_2__ {int /*<<< orphan*/  SmiCommand; int /*<<< orphan*/  XPmTimerBlock; int /*<<< orphan*/  XPm2ControlBlock; int /*<<< orphan*/  XPm1bControlBlock; int /*<<< orphan*/  XPm1aControlBlock; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_INSERT_BITS (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ACPI_PM1_CONTROL_PRESERVED_BITS ; 
 int ACPI_PM1_STATUS_PRESERVED_BITS ; 
 int /*<<< orphan*/  ACPI_PM2_CONTROL_PRESERVED_BITS ; 
#define  ACPI_REGISTER_PM1_CONTROL 133 
#define  ACPI_REGISTER_PM1_ENABLE 132 
#define  ACPI_REGISTER_PM1_STATUS 131 
#define  ACPI_REGISTER_PM2_CONTROL 130 
#define  ACPI_REGISTER_PM_TIMER 129 
#define  ACPI_REGISTER_SMI_COMMAND_BLOCK 128 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 TYPE_1__ AcpiGbl_FADT ; 
 int /*<<< orphan*/  AcpiGbl_XPm1aEnable ; 
 int /*<<< orphan*/  AcpiGbl_XPm1aStatus ; 
 int /*<<< orphan*/  AcpiGbl_XPm1bEnable ; 
 int /*<<< orphan*/  AcpiGbl_XPm1bStatus ; 
 int /*<<< orphan*/  AcpiHwRead (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiHwReadMultiple (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiHwWrite (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiHwWriteMultiple (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiHwWritePort (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  HwRegisterWrite ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiHwRegisterWrite (
    UINT32                  RegisterId,
    UINT32                  Value)
{
    ACPI_STATUS             Status;
    UINT32                  ReadValue;
    UINT64                  ReadValue64;


    ACPI_FUNCTION_TRACE (HwRegisterWrite);


    switch (RegisterId)
    {
    case ACPI_REGISTER_PM1_STATUS:           /* PM1 A/B: 16-bit access each */
        /*
         * Handle the "ignored" bit in PM1 Status. According to the ACPI
         * specification, ignored bits are to be preserved when writing.
         * Normally, this would mean a read/modify/write sequence. However,
         * preserving a bit in the status register is different. Writing a
         * one clears the status, and writing a zero preserves the status.
         * Therefore, we must always write zero to the ignored bit.
         *
         * This behavior is clarified in the ACPI 4.0 specification.
         */
        Value &= ~ACPI_PM1_STATUS_PRESERVED_BITS;

        Status = AcpiHwWriteMultiple (Value,
            &AcpiGbl_XPm1aStatus,
            &AcpiGbl_XPm1bStatus);
        break;

    case ACPI_REGISTER_PM1_ENABLE:           /* PM1 A/B: 16-bit access each */

        Status = AcpiHwWriteMultiple (Value,
            &AcpiGbl_XPm1aEnable,
            &AcpiGbl_XPm1bEnable);
        break;

    case ACPI_REGISTER_PM1_CONTROL:          /* PM1 A/B: 16-bit access each */
        /*
         * Perform a read first to preserve certain bits (per ACPI spec)
         * Note: This includes SCI_EN, we never want to change this bit
         */
        Status = AcpiHwReadMultiple (&ReadValue,
            &AcpiGbl_FADT.XPm1aControlBlock,
            &AcpiGbl_FADT.XPm1bControlBlock);
        if (ACPI_FAILURE (Status))
        {
            goto Exit;
        }

        /* Insert the bits to be preserved */

        ACPI_INSERT_BITS (Value, ACPI_PM1_CONTROL_PRESERVED_BITS, ReadValue);

        /* Now we can write the data */

        Status = AcpiHwWriteMultiple (Value,
            &AcpiGbl_FADT.XPm1aControlBlock,
            &AcpiGbl_FADT.XPm1bControlBlock);
        break;

    case ACPI_REGISTER_PM2_CONTROL:          /* 8-bit access */
        /*
         * For control registers, all reserved bits must be preserved,
         * as per the ACPI spec.
         */
        Status = AcpiHwRead (&ReadValue64, &AcpiGbl_FADT.XPm2ControlBlock);
        if (ACPI_FAILURE (Status))
        {
            goto Exit;
        }
        ReadValue = (UINT32) ReadValue64;

        /* Insert the bits to be preserved */

        ACPI_INSERT_BITS (Value, ACPI_PM2_CONTROL_PRESERVED_BITS, ReadValue);

        Status = AcpiHwWrite (Value, &AcpiGbl_FADT.XPm2ControlBlock);
        break;

    case ACPI_REGISTER_PM_TIMER:             /* 32-bit access */

        Status = AcpiHwWrite (Value, &AcpiGbl_FADT.XPmTimerBlock);
        break;

    case ACPI_REGISTER_SMI_COMMAND_BLOCK:    /* 8-bit access */

        /* SMI_CMD is currently always in IO space */

        Status = AcpiHwWritePort (AcpiGbl_FADT.SmiCommand, Value, 8);
        break;

    default:

        ACPI_ERROR ((AE_INFO, "Unknown Register ID: 0x%X",
            RegisterId));
        Status = AE_BAD_PARAMETER;
        break;
    }

Exit:
    return_ACPI_STATUS (Status);
}