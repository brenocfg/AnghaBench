#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ protocol; TYPE_2__* manager; TYPE_1__* link; } ;
struct TYPE_9__ {struct TYPE_9__* servers_next; } ;
struct TYPE_8__ {TYPE_3__* dns_servers; } ;
struct TYPE_7__ {TYPE_3__* dns_servers; } ;
typedef  TYPE_3__ DnsServer ;
typedef  TYPE_4__ DnsScope ;

/* Variables and functions */
 scalar_t__ DNS_PROTOCOL_DNS ; 
 int /*<<< orphan*/  assert (TYPE_4__*) ; 

unsigned dns_scope_get_n_dns_servers(DnsScope *s) {
        unsigned n = 0;
        DnsServer *i;

        assert(s);

        if (s->protocol != DNS_PROTOCOL_DNS)
                return 0;

        if (s->link)
                i = s->link->dns_servers;
        else
                i = s->manager->dns_servers;

        for (; i; i = i->servers_next)
                n++;

        return n;
}