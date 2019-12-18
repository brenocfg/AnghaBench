#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union in_addr_union {int dummy; } in_addr_union ;
struct TYPE_8__ {scalar_t__ family; scalar_t__ scope; int ip_masquerade_done; int /*<<< orphan*/  prefixlen; union in_addr_union in_addr; TYPE_1__* network; } ;
struct TYPE_7__ {scalar_t__ ip_masquerade; } ;
typedef  TYPE_2__ Link ;
typedef  TYPE_2__ Address ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ RT_SCOPE_LINK ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int fw_add_masquerade (int,scalar_t__,int /*<<< orphan*/ ,union in_addr_union*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_addr_mask (scalar_t__,union in_addr_union*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int address_establish(Address *address, Link *link) {
        bool masq;
        int r;

        assert(address);
        assert(link);

        masq = link->network &&
               link->network->ip_masquerade &&
               address->family == AF_INET &&
               address->scope < RT_SCOPE_LINK;

        /* Add firewall entry if this is requested */
        if (address->ip_masquerade_done != masq) {
                union in_addr_union masked = address->in_addr;
                in_addr_mask(address->family, &masked, address->prefixlen);

                r = fw_add_masquerade(masq, AF_INET, 0, &masked, address->prefixlen, NULL, NULL, 0);
                if (r < 0)
                        return r;

                address->ip_masquerade_done = masq;
        }

        return 0;
}