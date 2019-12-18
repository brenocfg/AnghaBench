#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int id; int oif; int family; int /*<<< orphan*/  gw; } ;
typedef  TYPE_1__ NextHop ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int CMP (int,int) ; 
 int /*<<< orphan*/  FAMILY_ADDRESS_SIZE (int) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nexthop_compare_func(const NextHop *a, const NextHop *b) {
        int r;

        r = CMP(a->id, b->id);
        if (r != 0)
                return r;

        r = CMP(a->oif, b->oif);
        if (r != 0)
                return r;

        r = CMP(a->family, b->family);
        if (r != 0)
                return r;

        switch (a->family) {
        case AF_INET:
        case AF_INET6:

                r = memcmp(&a->gw, &b->gw, FAMILY_ADDRESS_SIZE(a->family));
                if (r != 0)
                        return r;

                return 0;
        default:
                /* treat any other address family as AF_UNSPEC */
                return 0;
        }
}