#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct in6_addr {int* s6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
union in_addr_union {struct in6_addr in6; TYPE_1__ in; } ;
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  assert (union in_addr_union*) ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe32 (int) ; 

int in_addr_prefix_next(int family, union in_addr_union *u, unsigned prefixlen) {
        assert(u);

        /* Increases the network part of an address by one. Returns
         * positive it that succeeds, or 0 if this overflows. */

        if (prefixlen <= 0)
                return 0;

        if (family == AF_INET) {
                uint32_t c, n;

                if (prefixlen > 32)
                        prefixlen = 32;

                c = be32toh(u->in.s_addr);
                n = c + (1UL << (32 - prefixlen));
                if (n < c)
                        return 0;
                n &= 0xFFFFFFFFUL << (32 - prefixlen);

                u->in.s_addr = htobe32(n);
                return 1;
        }

        if (family == AF_INET6) {
                struct in6_addr add = {}, result;
                uint8_t overflow = 0;
                unsigned i;

                if (prefixlen > 128)
                        prefixlen = 128;

                /* First calculate what we have to add */
                add.s6_addr[(prefixlen-1) / 8] = 1 << (7 - (prefixlen-1) % 8);

                for (i = 16; i > 0; i--) {
                        unsigned j = i - 1;

                        result.s6_addr[j] = u->in6.s6_addr[j] + add.s6_addr[j] + overflow;
                        overflow = (result.s6_addr[j] < u->in6.s6_addr[j]);
                }

                if (overflow)
                        return 0;

                u->in6 = result;
                return 1;
        }

        return -EAFNOSUPPORT;
}