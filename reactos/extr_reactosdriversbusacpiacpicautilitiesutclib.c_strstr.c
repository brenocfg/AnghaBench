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
 scalar_t__ memcmp (char*,char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

char *
strstr (
    char                    *String1,
    char                    *String2)
{
    ACPI_SIZE               Length;


    Length = strlen (String2);
    if (!Length)
    {
        return (String1);
    }

    while (strlen (String1) >= Length)
    {
        if (memcmp (String1, String2, Length) == 0)
        {
            return (String1);
        }
        String1++;
    }

    return (NULL);
}