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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
union in_addr_union {int /*<<< orphan*/  in6; TYPE_1__ in; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int EAFNOSUPPORT ; 
 int IN6_IS_ADDR_MULTICAST (int /*<<< orphan*/ *) ; 
 int IN_MULTICAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (union in_addr_union const*) ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 

int in_addr_is_multicast(int family, const union in_addr_union *u) {
        assert(u);

        if (family == AF_INET)
                return IN_MULTICAST(be32toh(u->in.s_addr));

        if (family == AF_INET6)
                return IN6_IS_ADDR_MULTICAST(&u->in6);

        return -EAFNOSUPPORT;
}