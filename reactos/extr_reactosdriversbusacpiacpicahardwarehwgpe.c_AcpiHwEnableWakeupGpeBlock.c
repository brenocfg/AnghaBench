#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_6__ {size_t RegisterCount; TYPE_1__* RegisterInfo; } ;
struct TYPE_5__ {int /*<<< orphan*/  EnableForWake; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_GPE_XRUPT_INFO ;
typedef  TYPE_1__ ACPI_GPE_REGISTER_INFO ;
typedef  TYPE_2__ ACPI_GPE_BLOCK_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiHwGpeEnableWrite (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static ACPI_STATUS
AcpiHwEnableWakeupGpeBlock (
    ACPI_GPE_XRUPT_INFO     *GpeXruptInfo,
    ACPI_GPE_BLOCK_INFO     *GpeBlock,
    void                    *Context)
{
    UINT32                  i;
    ACPI_STATUS             Status;
    ACPI_GPE_REGISTER_INFO  *GpeRegisterInfo;


    /* Examine each GPE Register within the block */

    for (i = 0; i < GpeBlock->RegisterCount; i++)
    {
        GpeRegisterInfo = &GpeBlock->RegisterInfo[i];

        /*
         * Enable all "wake" GPEs in this register and disable the
         * remaining ones.
         */
        Status = AcpiHwGpeEnableWrite (GpeRegisterInfo->EnableForWake,
            GpeRegisterInfo);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }
    }

    return (AE_OK);
}