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
struct TYPE_7__ {scalar_t__ dns_servers; scalar_t__ fallback_dns_servers; TYPE_1__* current_dns_server; } ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ servers_next; scalar_t__ linked; } ;
typedef  TYPE_2__ Manager ;

/* Variables and functions */
 scalar_t__ DNS_SERVER_FALLBACK ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  manager_set_dns_server (TYPE_2__*,scalar_t__) ; 

void manager_next_dns_server(Manager *m) {
        assert(m);

        /* If there's currently no DNS server set, then the next
         * manager_get_dns_server() will find one */
        if (!m->current_dns_server)
                return;

        /* Change to the next one, but make sure to follow the linked
         * list only if the server is still linked. */
        if (m->current_dns_server->linked && m->current_dns_server->servers_next) {
                manager_set_dns_server(m, m->current_dns_server->servers_next);
                return;
        }

        /* If there was no next one, then start from the beginning of
         * the list */
        if (m->current_dns_server->type == DNS_SERVER_FALLBACK)
                manager_set_dns_server(m, m->fallback_dns_servers);
        else
                manager_set_dns_server(m, m->dns_servers);
}