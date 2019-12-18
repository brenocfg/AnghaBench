#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ dns_servers; TYPE_1__* current_dns_server; } ;
struct TYPE_6__ {scalar_t__ servers_next; scalar_t__ linked; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  link_set_dns_server (TYPE_2__*,scalar_t__) ; 

void link_next_dns_server(Link *l) {
        assert(l);

        if (!l->current_dns_server)
                return;

        /* Change to the next one, but make sure to follow the linked
         * list only if this server is actually still linked. */
        if (l->current_dns_server->linked && l->current_dns_server->servers_next) {
                link_set_dns_server(l, l->current_dns_server->servers_next);
                return;
        }

        link_set_dns_server(l, l->dns_servers);
}