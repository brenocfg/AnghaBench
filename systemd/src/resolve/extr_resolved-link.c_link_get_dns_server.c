#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * current_dns_server; int /*<<< orphan*/  dns_servers; } ;
typedef  TYPE_1__ Link ;
typedef  int /*<<< orphan*/  DnsServer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  link_set_dns_server (TYPE_1__*,int /*<<< orphan*/ ) ; 

DnsServer *link_get_dns_server(Link *l) {
        assert(l);

        if (!l->current_dns_server)
                link_set_dns_server(l, l->dns_servers);

        return l->current_dns_server;
}