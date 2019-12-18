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
 int /*<<< orphan*/  DIGITS ; 
 int EINVAL ; 
 int /*<<< orphan*/  strspn (char const*,int /*<<< orphan*/ ) ; 

int parse_fractional_part_u(const char **p, size_t digits, unsigned *res) {
        size_t i;
        unsigned val = 0;
        const char *s;

        s = *p;

        /* accept any number of digits, strtoull is limited to 19 */
        for (i=0; i < digits; i++,s++) {
                if (*s < '0' || *s > '9') {
                        if (i == 0)
                                return -EINVAL;

                        /* too few digits, pad with 0 */
                        for (; i < digits; i++)
                                val *= 10;

                        break;
                }

                val *= 10;
                val += *s - '0';
        }

        /* maybe round up */
        if (*s >= '5' && *s <= '9')
                val++;

        s += strspn(s, DIGITS);

        *p = s;
        *res = val;

        return 0;
}