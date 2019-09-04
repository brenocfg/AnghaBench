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

/* Variables and functions */

int
strcmp (
    const char              *String1,
    const char              *String2)
{


    for ( ; (*String1 == *String2); String2++)
    {
        if (!*String1++)
        {
            return (0);
        }
    }

    return ((unsigned char) *String1 - (unsigned char) *String2);
}