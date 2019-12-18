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
struct TYPE_2__ {scalar_t__* s6_addr32; } ;
union in_addr_union {TYPE_1__ in6; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  assert (union in_addr_union const*) ; 
 int in4_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int in_addr_equal(int family, const union in_addr_union *a, const union in_addr_union *b) {
        assert(a);
        assert(b);

        if (family == AF_INET)
                return in4_addr_equal(&a->in, &b->in);

        if (family == AF_INET6)
                return
                        a->in6.s6_addr32[0] == b->in6.s6_addr32[0] &&
                        a->in6.s6_addr32[1] == b->in6.s6_addr32[1] &&
                        a->in6.s6_addr32[2] == b->in6.s6_addr32[2] &&
                        a->in6.s6_addr32[3] == b->in6.s6_addr32[3];

        return -EAFNOSUPPORT;
}