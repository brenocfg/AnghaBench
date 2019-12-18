#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  union in_addr_union {int dummy; } in_addr_union ;
struct in6_addr {int dummy; } ;
struct TYPE_10__ {struct TYPE_10__* label; scalar_t__ section; TYPE_2__* link; int /*<<< orphan*/  in_addr; TYPE_1__* network; } ;
struct TYPE_9__ {int /*<<< orphan*/  ipv6ll_address; int /*<<< orphan*/  addresses_foreign; int /*<<< orphan*/  addresses; } ;
struct TYPE_8__ {scalar_t__ n_static_addresses; int /*<<< orphan*/  addresses_by_section; int /*<<< orphan*/  static_addresses; } ;
typedef  TYPE_3__ Address ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  addresses ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ in_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,union in_addr_union const*) ; 
 int /*<<< orphan*/  memzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  network_config_section_free (scalar_t__) ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,TYPE_3__*) ; 

void address_free(Address *address) {
        if (!address)
                return;

        if (address->network) {
                LIST_REMOVE(addresses, address->network->static_addresses, address);
                assert(address->network->n_static_addresses > 0);
                address->network->n_static_addresses--;

                if (address->section)
                        hashmap_remove(address->network->addresses_by_section, address->section);
        }

        if (address->link) {
                set_remove(address->link->addresses, address);
                set_remove(address->link->addresses_foreign, address);

                if (in_addr_equal(AF_INET6, &address->in_addr, (const union in_addr_union *) &address->link->ipv6ll_address))
                        memzero(&address->link->ipv6ll_address, sizeof(struct in6_addr));
        }

        network_config_section_free(address->section);
        free(address->label);
        free(address);
}