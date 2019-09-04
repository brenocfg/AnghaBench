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
typedef  scalar_t__ ACPI_SIZE ;

/* Variables and functions */
 scalar_t__ ACPI_SIZE_MAX ; 

int
strncmp (
    const char              *String1,
    const char              *String2,
    ACPI_SIZE               Count)
{


    for ( ; Count-- && (*String1 == *String2); String2++)
    {
        if (!*String1++)
        {
            return (0);
        }
    }

    return ((Count == ACPI_SIZE_MAX) ? 0 : ((unsigned char) *String1 -
        (unsigned char) *String2));
}