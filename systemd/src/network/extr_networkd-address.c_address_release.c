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
typedef  union in_addr_union {int dummy; } in_addr_union ;
struct TYPE_4__ {int ip_masquerade_done; int /*<<< orphan*/  prefixlen; int /*<<< orphan*/  family; union in_addr_union in_addr; struct TYPE_4__* link; } ;
typedef  TYPE_1__ Address ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int fw_add_masquerade (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union in_addr_union*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_addr_mask (int /*<<< orphan*/ ,union in_addr_union*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int address_release(Address *address) {
        int r;

        assert(address);
        assert(address->link);

        /* Remove masquerading firewall entry if it was added */
        if (address->ip_masquerade_done) {
                union in_addr_union masked = address->in_addr;
                in_addr_mask(address->family, &masked, address->prefixlen);

                r = fw_add_masquerade(false, AF_INET, 0, &masked, address->prefixlen, NULL, NULL, 0);
                if (r < 0)
                        return r;

                address->ip_masquerade_done = false;
        }

        return 0;
}