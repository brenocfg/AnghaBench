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
struct TYPE_4__ {int family; int dst_prefixlen; int src_prefixlen; int tos; int priority; int table; int protocol; int scope; int type; int initcwnd; int initrwnd; int /*<<< orphan*/  prefsrc; int /*<<< orphan*/  gw; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
typedef  TYPE_1__ Route ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int CMP (int,int) ; 
 int /*<<< orphan*/  FAMILY_ADDRESS_SIZE (int) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int route_compare_func(const Route *a, const Route *b) {
        int r;

        r = CMP(a->family, b->family);
        if (r != 0)
                return r;

        switch (a->family) {
        case AF_INET:
        case AF_INET6:
                r = CMP(a->dst_prefixlen, b->dst_prefixlen);
                if (r != 0)
                        return r;

                r = memcmp(&a->dst, &b->dst, FAMILY_ADDRESS_SIZE(a->family));
                if (r != 0)
                        return r;

                r = CMP(a->src_prefixlen, b->src_prefixlen);
                if (r != 0)
                        return r;

                r = memcmp(&a->src, &b->src, FAMILY_ADDRESS_SIZE(a->family));
                if (r != 0)
                        return r;

                r = memcmp(&a->gw, &b->gw, FAMILY_ADDRESS_SIZE(a->family));
                if (r != 0)
                        return r;

                r = memcmp(&a->prefsrc, &b->prefsrc, FAMILY_ADDRESS_SIZE(a->family));
                if (r != 0)
                        return r;

                r = CMP(a->tos, b->tos);
                if (r != 0)
                        return r;

                r = CMP(a->priority, b->priority);
                if (r != 0)
                        return r;

                r = CMP(a->table, b->table);
                if (r != 0)
                        return r;

                r = CMP(a->protocol, b->protocol);
                if (r != 0)
                        return r;

                r = CMP(a->scope, b->scope);
                if (r != 0)
                        return r;

                r = CMP(a->type, b->type);
                if (r != 0)
                        return r;

                r = CMP(a->initcwnd, b->initcwnd);
                if (r != 0)
                        return r;

                r = CMP(a->initrwnd, b->initrwnd);
                if (r != 0)
                        return r;

                return 0;
        default:
                /* treat any other address family as AF_UNSPEC */
                return 0;
        }
}