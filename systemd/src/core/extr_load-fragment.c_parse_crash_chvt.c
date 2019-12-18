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
 int parse_boolean (char const*) ; 
 scalar_t__ safe_atoi (char const*,int*) ; 

int parse_crash_chvt(const char *value, int *data) {
        int b;

        if (safe_atoi(value, data) >= 0)
                return 0;

        b = parse_boolean(value);
        if (b < 0)
                return b;

        if (b > 0)
                *data = 0; /* switch to where kmsg goes */
        else
                *data = -1; /* turn off switching */

        return 0;
}