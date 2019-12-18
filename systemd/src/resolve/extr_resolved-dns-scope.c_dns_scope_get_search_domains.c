#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ protocol; TYPE_2__* manager; TYPE_1__* link; } ;
struct TYPE_7__ {int /*<<< orphan*/ * search_domains; } ;
struct TYPE_6__ {int /*<<< orphan*/ * search_domains; } ;
typedef  int /*<<< orphan*/  DnsSearchDomain ;
typedef  TYPE_3__ DnsScope ;

/* Variables and functions */
 scalar_t__ DNS_PROTOCOL_DNS ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 

DnsSearchDomain *dns_scope_get_search_domains(DnsScope *s) {
        assert(s);

        if (s->protocol != DNS_PROTOCOL_DNS)
                return NULL;

        if (s->link)
                return s->link->search_domains;

        return s->manager->search_domains;
}