#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  type; } ;
struct TYPE_14__ {TYPE_1__* unicast_scope; TYPE_3__* current_dns_server; } ;
struct TYPE_13__ {int /*<<< orphan*/  cache; } ;
typedef  TYPE_2__ Manager ;
typedef  TYPE_3__ DnsServer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  dns_cache_flush (int /*<<< orphan*/ *) ; 
 TYPE_3__* dns_server_ref (TYPE_3__*) ; 
 int /*<<< orphan*/  dns_server_string (TYPE_3__*) ; 
 int /*<<< orphan*/  dns_server_type_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_server_unref (TYPE_3__*) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manager_send_changed (TYPE_2__*,char*) ; 

DnsServer *manager_set_dns_server(Manager *m, DnsServer *s) {
        assert(m);

        if (m->current_dns_server == s)
                return s;

        if (s)
                log_debug("Switching to %s DNS server %s.",
                          dns_server_type_to_string(s->type),
                          dns_server_string(s));

        dns_server_unref(m->current_dns_server);
        m->current_dns_server = dns_server_ref(s);

        if (m->unicast_scope)
                dns_cache_flush(&m->unicast_scope->cache);

        (void) manager_send_changed(m, "CurrentDNSServer");

        return s;
}