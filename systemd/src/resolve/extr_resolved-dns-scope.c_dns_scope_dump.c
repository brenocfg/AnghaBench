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
struct TYPE_6__ {scalar_t__ family; int /*<<< orphan*/  cache; int /*<<< orphan*/  zone; TYPE_1__* link; int /*<<< orphan*/  protocol; } ;
struct TYPE_5__ {char* ifname; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_2__ DnsScope ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 char* af_to_name (scalar_t__) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  dns_cache_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dns_cache_is_empty (int /*<<< orphan*/ *) ; 
 char* dns_protocol_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_zone_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dns_zone_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stdout ; 

void dns_scope_dump(DnsScope *s, FILE *f) {
        assert(s);

        if (!f)
                f = stdout;

        fputs("[Scope protocol=", f);
        fputs(dns_protocol_to_string(s->protocol), f);

        if (s->link) {
                fputs(" interface=", f);
                fputs(s->link->ifname, f);
        }

        if (s->family != AF_UNSPEC) {
                fputs(" family=", f);
                fputs(af_to_name(s->family), f);
        }

        fputs("]\n", f);

        if (!dns_zone_is_empty(&s->zone)) {
                fputs("ZONE:\n", f);
                dns_zone_dump(&s->zone, f);
        }

        if (!dns_cache_is_empty(&s->cache)) {
                fputs("CACHE:\n", f);
                dns_cache_dump(&s->cache, f);
        }
}