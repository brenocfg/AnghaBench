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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ ascii_tolower (char const) ; 

int ascii_strcasecmp_n(const char *a, const char *b, size_t n) {

        for (; n > 0; a++, b++, n--) {
                int x, y;

                x = (int) (uint8_t) ascii_tolower(*a);
                y = (int) (uint8_t) ascii_tolower(*b);

                if (x != y)
                        return x - y;
        }

        return 0;
}