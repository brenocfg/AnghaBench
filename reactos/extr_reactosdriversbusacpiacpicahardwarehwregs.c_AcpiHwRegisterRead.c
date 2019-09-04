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
typedef  scalar_t__ UINT64 ;
typedef  int UINT32 ;
struct TYPE_2__ {int /*<<< orphan*/  SmiCommand; int /*<<< orphan*/  XPmTimerBlock; int /*<<< orphan*/  XPm2ControlBlock; int /*<<< orphan*/  XPm1bControlBlock; int /*<<< orphan*/  XPm1aControlBlock; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_PM1_CONTROL_WRITEONLY_BITS ; 
#define  ACPI_REGISTER_PM1_CONTROL 133 
#define  ACPI_REGISTER_PM1_ENABLE 132 
#define  ACPI_REGISTER_PM1_STATUS 131 
#define  ACPI_REGISTER_PM2_CONTROL 130 
#define  ACPI_REGISTER_PM_TIMER 129 
#define  ACPI_REGISTER_SMI_COMMAND_BLOCK 128 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 TYPE_1__ AcpiGbl_FADT ; 
 int /*<<< orphan*/  AcpiGbl_XPm1aEnable ; 
 int /*<<< orphan*/  AcpiGbl_XPm1aStatus ; 
 int /*<<< orphan*/  AcpiGbl_XPm1bEnable ; 
 int /*<<< orphan*/  AcpiGbl_XPm1bStatus ; 
 int /*<<< orphan*/  AcpiHwRead (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiHwReadMultiple (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiHwReadPort (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  HwRegisterRead ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiHwRegisterRead (
    UINT32                  RegisterId,
    UINT32                  *ReturnValue)
{
    UINT32                  Value = 0;
    UINT64                  Value64;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (HwRegisterRead);


    switch (RegisterId)
    {
    case ACPI_REGISTER_PM1_STATUS:           /* PM1 A/B: 16-bit access each */

        Status = AcpiHwReadMultiple (&Value,
            &AcpiGbl_XPm1aStatus,
            &AcpiGbl_XPm1bStatus);
        break;

    case ACPI_REGISTER_PM1_ENABLE:           /* PM1 A/B: 16-bit access each */

        Status = AcpiHwReadMultiple (&Value,
            &AcpiGbl_XPm1aEnable,
            &AcpiGbl_XPm1bEnable);
        break;

    case ACPI_REGISTER_PM1_CONTROL:          /* PM1 A/B: 16-bit access each */

        Status = AcpiHwReadMultiple (&Value,
            &AcpiGbl_FADT.XPm1aControlBlock,
            &AcpiGbl_FADT.XPm1bControlBlock);

        /*
         * Zero the write-only bits. From the ACPI specification, "Hardware
         * Write-Only Bits": "Upon reads to registers with write-only bits,
         * software masks out all write-only bits."
         */
        Value &= ~ACPI_PM1_CONTROL_WRITEONLY_BITS;
        break;

    case ACPI_REGISTER_PM2_CONTROL:          /* 8-bit access */

        Status = AcpiHwRead (&Value64, &AcpiGbl_FADT.XPm2ControlBlock);
        if (ACPI_SUCCESS (Status))
        {
            Value = (UINT32) Value64;
        }
        break;

    case ACPI_REGISTER_PM_TIMER:             /* 32-bit access */

        Status = AcpiHwRead (&Value64, &AcpiGbl_FADT.XPmTimerBlock);
        if (ACPI_SUCCESS (Status))
        {
            Value = (UINT32) Value64;
        }

        break;

    case ACPI_REGISTER_SMI_COMMAND_BLOCK:    /* 8-bit access */

        Status = AcpiHwReadPort (AcpiGbl_FADT.SmiCommand, &Value, 8);
        break;

    default:

        ACPI_ERROR ((AE_INFO, "Unknown Register ID: 0x%X",
            RegisterId));
        Status = AE_BAD_PARAMETER;
        break;
    }

    if (ACPI_SUCCESS (Status))
    {
        *ReturnValue = (UINT32) Value;
    }

    return_ACPI_STATUS (Status);
}