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
 int /*<<< orphan*/  assert (char const*) ; 

char *ascii_is_valid_n(const char *str, size_t len) {
        size_t i;

        /* Very similar to ascii_is_valid(), but checks exactly len
         * bytes and rejects any NULs in that range. */

        assert(str);

        for (i = 0; i < len; i++)
                if ((unsigned char) str[i] >= 128 || str[i] == 0)
                        return NULL;

        return (char*) str;
}