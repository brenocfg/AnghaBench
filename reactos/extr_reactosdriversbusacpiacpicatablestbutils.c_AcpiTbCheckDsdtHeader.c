#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ Length; scalar_t__ Checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BIOS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 TYPE_1__* AcpiGbl_DSDT ; 
 TYPE_1__ AcpiGbl_OriginalDsdtHeader ; 
 int /*<<< orphan*/  AcpiTbPrintTableHeader (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
AcpiTbCheckDsdtHeader (
    void)
{

    /* Compare original length and checksum to current values */

    if (AcpiGbl_OriginalDsdtHeader.Length != AcpiGbl_DSDT->Length ||
        AcpiGbl_OriginalDsdtHeader.Checksum != AcpiGbl_DSDT->Checksum)
    {
        ACPI_BIOS_ERROR ((AE_INFO,
            "The DSDT has been corrupted or replaced - "
            "old, new headers below"));

        AcpiTbPrintTableHeader (0, &AcpiGbl_OriginalDsdtHeader);
        AcpiTbPrintTableHeader (0, AcpiGbl_DSDT);

        /* Disable further error messages */

        AcpiGbl_OriginalDsdtHeader.Length = AcpiGbl_DSDT->Length;
        AcpiGbl_OriginalDsdtHeader.Checksum = AcpiGbl_DSDT->Checksum;
    }
}