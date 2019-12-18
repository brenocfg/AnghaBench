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
struct TYPE_4__ {int family; int dst_prefixlen; int dst; int src_prefixlen; int src; int gw; int prefsrc; int tos; int priority; int table; int protocol; int scope; int type; int initcwnd; int initrwnd; } ;
typedef  TYPE_1__ Route ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int FAMILY_ADDRESS_SIZE (int) ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  siphash24_compress (int*,int,struct siphash*) ; 

__attribute__((used)) static void route_hash_func(const Route *route, struct siphash *state) {
        assert(route);

        siphash24_compress(&route->family, sizeof(route->family), state);

        switch (route->family) {
        case AF_INET:
        case AF_INET6:
                siphash24_compress(&route->dst_prefixlen, sizeof(route->dst_prefixlen), state);
                siphash24_compress(&route->dst, FAMILY_ADDRESS_SIZE(route->family), state);

                siphash24_compress(&route->src_prefixlen, sizeof(route->src_prefixlen), state);
                siphash24_compress(&route->src, FAMILY_ADDRESS_SIZE(route->family), state);

                siphash24_compress(&route->gw, FAMILY_ADDRESS_SIZE(route->family), state);

                siphash24_compress(&route->prefsrc, FAMILY_ADDRESS_SIZE(route->family), state);

                siphash24_compress(&route->tos, sizeof(route->tos), state);
                siphash24_compress(&route->priority, sizeof(route->priority), state);
                siphash24_compress(&route->table, sizeof(route->table), state);
                siphash24_compress(&route->protocol, sizeof(route->protocol), state);
                siphash24_compress(&route->scope, sizeof(route->scope), state);
                siphash24_compress(&route->type, sizeof(route->type), state);

                siphash24_compress(&route->initcwnd, sizeof(route->initcwnd), state);
                siphash24_compress(&route->initrwnd, sizeof(route->initrwnd), state);

                break;
        default:
                /* treat any other address family as AF_UNSPEC */
                break;
        }
}