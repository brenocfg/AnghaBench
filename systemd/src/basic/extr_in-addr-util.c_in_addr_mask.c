#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* s6_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
union in_addr_union {TYPE_1__ in6; TYPE_2__ in; } ;
typedef  int uint8_t ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  assert (union in_addr_union*) ; 
 int /*<<< orphan*/  in4_addr_prefixlen_to_netmask (struct in_addr*,unsigned char) ; 

int in_addr_mask(int family, union in_addr_union *addr, unsigned char prefixlen) {
        assert(addr);

        if (family == AF_INET) {
                struct in_addr mask;

                if (!in4_addr_prefixlen_to_netmask(&mask, prefixlen))
                        return -EINVAL;

                addr->in.s_addr &= mask.s_addr;
                return 0;
        }

        if (family == AF_INET6) {
                unsigned i;

                for (i = 0; i < 16; i++) {
                        uint8_t mask;

                        if (prefixlen >= 8) {
                                mask = 0xFF;
                                prefixlen -= 8;
                        } else {
                                mask = 0xFF << (8 - prefixlen);
                                prefixlen = 0;
                        }

                        addr->in6.s6_addr[i] &= mask;
                }

                return 0;
        }

        return -EAFNOSUPPORT;
}