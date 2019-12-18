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

__attribute__((used)) static bool tar_is_number(const char *data, size_t size)
{
    size_t i;

    for (i = 0; i < size; i++) {
        if ((data[i] < '0' || '7' < data[i]) && data[i] != ' ' && data[i] != '\0')
            return false;
    }

    return true;
}