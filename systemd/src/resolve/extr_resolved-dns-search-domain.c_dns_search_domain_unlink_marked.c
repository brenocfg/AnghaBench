#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ marked; struct TYPE_4__* domains_next; } ;
typedef  TYPE_1__ DnsSearchDomain ;

/* Variables and functions */
 int /*<<< orphan*/  dns_search_domain_unlink (TYPE_1__*) ; 

void dns_search_domain_unlink_marked(DnsSearchDomain *first) {
        DnsSearchDomain *next;

        if (!first)
                return;

        next = first->domains_next;

        if (first->marked)
                dns_search_domain_unlink(first);

        dns_search_domain_unlink_marked(next);
}