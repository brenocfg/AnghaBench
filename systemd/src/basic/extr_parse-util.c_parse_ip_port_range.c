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
typedef  unsigned int uint16_t ;

/* Variables and functions */
 int EINVAL ; 
 int parse_range (char const*,unsigned int*,unsigned int*) ; 

int parse_ip_port_range(const char *s, uint16_t *low, uint16_t *high) {
        unsigned l, h;
        int r;

        r = parse_range(s, &l, &h);
        if (r < 0)
                return r;

        if (l <= 0 || l > 65535 || h <= 0 || h > 65535)
                return -EINVAL;

        if (h < l)
                return -EINVAL;

        *low = l;
        *high = h;

        return 0;
}