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

char *
strncpy (
    char                    *DstString,
    const char              *SrcString,
    ACPI_SIZE               Count)
{
    char                    *String = DstString;


    /* Copy the string */

    for (String = DstString;
        Count && (Count--, (*String++ = *SrcString++)); )
    {;}

    /* Pad with nulls if necessary */

    while (Count--)
    {
        *String = 0;
        String++;
    }

    /* Return original pointer */

    return (DstString);
}