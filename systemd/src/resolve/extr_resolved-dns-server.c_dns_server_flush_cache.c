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
struct TYPE_10__ {int /*<<< orphan*/  cache; } ;
struct TYPE_9__ {TYPE_2__* manager; TYPE_1__* link; } ;
struct TYPE_8__ {TYPE_4__* unicast_scope; TYPE_3__* current_dns_server; } ;
struct TYPE_7__ {TYPE_4__* unicast_scope; TYPE_3__* current_dns_server; } ;
typedef  TYPE_3__ DnsServer ;
typedef  TYPE_4__ DnsScope ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  dns_cache_flush (int /*<<< orphan*/ *) ; 

void dns_server_flush_cache(DnsServer *s) {
        DnsServer *current;
        DnsScope *scope;

        assert(s);

        /* Flush the cache of the scope this server belongs to */

        current = s->link ? s->link->current_dns_server : s->manager->current_dns_server;
        if (current != s)
                return;

        scope = s->link ? s->link->unicast_scope : s->manager->unicast_scope;
        if (!scope)
                return;

        dns_cache_flush(&scope->cache);
}