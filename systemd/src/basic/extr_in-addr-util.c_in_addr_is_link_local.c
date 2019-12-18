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
union in_addr_union {int /*<<< orphan*/  in6; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int EAFNOSUPPORT ; 
 int IN6_IS_ADDR_LINKLOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (union in_addr_union const*) ; 
 int in4_addr_is_link_local (int /*<<< orphan*/ *) ; 

int in_addr_is_link_local(int family, const union in_addr_union *u) {
        assert(u);

        if (family == AF_INET)
                return in4_addr_is_link_local(&u->in);

        if (family == AF_INET6)
                return IN6_IS_ADDR_LINKLOCAL(&u->in6);

        return -EAFNOSUPPORT;
}