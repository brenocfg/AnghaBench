#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  ifname; int /*<<< orphan*/  state_file; int /*<<< orphan*/  mdns_ipv6_scope; int /*<<< orphan*/  mdns_ipv4_scope; int /*<<< orphan*/  llmnr_ipv6_scope; int /*<<< orphan*/  llmnr_ipv4_scope; int /*<<< orphan*/  unicast_scope; int /*<<< orphan*/  ifindex; TYPE_1__* manager; scalar_t__ addresses; } ;
struct TYPE_8__ {int /*<<< orphan*/  links; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  INT_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_scope_announce (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dns_scope_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_address_free (scalar_t__) ; 
 int /*<<< orphan*/  link_flush_settings (TYPE_2__*) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 

Link *link_free(Link *l) {
        if (!l)
                return NULL;

        /* Send goodbye messages. */
        dns_scope_announce(l->mdns_ipv4_scope, true);
        dns_scope_announce(l->mdns_ipv6_scope, true);

        link_flush_settings(l);

        while (l->addresses)
                (void) link_address_free(l->addresses);

        if (l->manager)
                hashmap_remove(l->manager->links, INT_TO_PTR(l->ifindex));

        dns_scope_free(l->unicast_scope);
        dns_scope_free(l->llmnr_ipv4_scope);
        dns_scope_free(l->llmnr_ipv6_scope);
        dns_scope_free(l->mdns_ipv4_scope);
        dns_scope_free(l->mdns_ipv6_scope);

        free(l->state_file);
        free(l->ifname);

        return mfree(l);
}