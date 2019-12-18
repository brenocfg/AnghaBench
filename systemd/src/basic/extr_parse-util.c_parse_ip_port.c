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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int EINVAL ; 
 int safe_atou16 (char const*,scalar_t__*) ; 

int parse_ip_port(const char *s, uint16_t *ret) {
        uint16_t l;
        int r;

        r = safe_atou16(s, &l);
        if (r < 0)
                return r;

        if (l == 0)
                return -EINVAL;

        *ret = (uint16_t) l;

        return 0;
}