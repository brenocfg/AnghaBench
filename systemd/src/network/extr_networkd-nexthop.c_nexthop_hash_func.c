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
struct siphash {int dummy; } ;
struct TYPE_4__ {int id; int oif; int family; int gw; } ;
typedef  TYPE_1__ NextHop ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int FAMILY_ADDRESS_SIZE (int) ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  siphash24_compress (int*,int,struct siphash*) ; 

__attribute__((used)) static void nexthop_hash_func(const NextHop *nexthop, struct siphash *state) {
        assert(nexthop);

        siphash24_compress(&nexthop->id, sizeof(nexthop->id), state);
        siphash24_compress(&nexthop->oif, sizeof(nexthop->oif), state);
        siphash24_compress(&nexthop->family, sizeof(nexthop->family), state);

        switch (nexthop->family) {
        case AF_INET:
        case AF_INET6:
                siphash24_compress(&nexthop->gw, FAMILY_ADDRESS_SIZE(nexthop->family), state);

                break;
        default:
                /* treat any other address family as AF_UNSPEC */
                break;
        }
}