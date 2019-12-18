#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* unicast_scope; int /*<<< orphan*/ * current_dns_server; int /*<<< orphan*/  ifname; } ;
struct TYPE_5__ {int /*<<< orphan*/  cache; } ;
typedef  TYPE_2__ Link ;
typedef  int /*<<< orphan*/  DnsServer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  dns_cache_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dns_server_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dns_server_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dns_server_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DnsServer* link_set_dns_server(Link *l, DnsServer *s) {
        assert(l);

        if (l->current_dns_server == s)
                return s;

        if (s)
                log_debug("Switching to DNS server %s for interface %s.", dns_server_string(s), l->ifname);

        dns_server_unref(l->current_dns_server);
        l->current_dns_server = dns_server_ref(s);

        if (l->unicast_scope)
                dns_cache_flush(&l->unicast_scope->cache);

        return s;
}