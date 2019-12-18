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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int EAFNOSUPPORT ; 
 int ERANGE ; 
 int FAMILY_ADDRESS_SIZE (int) ; 
 int /*<<< orphan*/  IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int safe_atou8 (char const*,int*) ; 

int in_addr_parse_prefixlen(int family, const char *p, unsigned char *ret) {
        uint8_t u;
        int r;

        if (!IN_SET(family, AF_INET, AF_INET6))
                return -EAFNOSUPPORT;

        r = safe_atou8(p, &u);
        if (r < 0)
                return r;

        if (u > FAMILY_ADDRESS_SIZE(family) * 8)
                return -ERANGE;

        *ret = u;
        return 0;
}