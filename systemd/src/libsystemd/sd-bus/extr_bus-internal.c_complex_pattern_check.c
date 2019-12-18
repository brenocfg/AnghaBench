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

__attribute__((used)) static bool complex_pattern_check(char c, const char *a, const char *b) {
        bool separator = false;

        if (!a && !b)
                return true;

        if (!a || !b)
                return false;

        for (;;) {
                if (*a != *b)
                        return (separator && (*a == 0 || *b == 0));

                if (*a == 0)
                        return true;

                separator = *a == c;

                a++, b++;
        }
}