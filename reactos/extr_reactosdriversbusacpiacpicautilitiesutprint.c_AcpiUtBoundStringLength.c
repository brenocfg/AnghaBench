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
typedef  scalar_t__ UINT32 ;
typedef  scalar_t__ ACPI_SIZE ;

/* Variables and functions */

__attribute__((used)) static ACPI_SIZE
AcpiUtBoundStringLength (
    const char              *String,
    ACPI_SIZE               Count)
{
    UINT32                  Length = 0;


    while (*String && Count)
    {
        Length++;
        String++;
        Count--;
    }

    return (Length);
}