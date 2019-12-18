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
typedef  struct in_addr const in_addr ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct in_addr const*) ; 
 int in4_addr_default_prefixlen (struct in_addr const*,unsigned char*) ; 
 int /*<<< orphan*/  in4_addr_prefixlen_to_netmask (struct in_addr const*,unsigned char) ; 

int in4_addr_default_subnet_mask(const struct in_addr *addr, struct in_addr *mask) {
        unsigned char prefixlen;
        int r;

        assert(addr);
        assert(mask);

        r = in4_addr_default_prefixlen(addr, &prefixlen);
        if (r < 0)
                return r;

        in4_addr_prefixlen_to_netmask(mask, prefixlen);
        return 0;
}