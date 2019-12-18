#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int marked; int type; TYPE_1__* manager; int /*<<< orphan*/  search_domains; struct TYPE_11__* link; int /*<<< orphan*/  domains_next; int /*<<< orphan*/  linked; } ;
struct TYPE_10__ {int /*<<< orphan*/  search_domains; } ;
typedef  TYPE_2__ DnsSearchDomain ;

/* Variables and functions */
#define  DNS_SEARCH_DOMAIN_LINK 129 
#define  DNS_SEARCH_DOMAIN_SYSTEM 128 
 int /*<<< orphan*/  LIST_FIND_TAIL (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  LIST_INSERT_AFTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  domains ; 

void dns_search_domain_move_back_and_unmark(DnsSearchDomain *d) {
        DnsSearchDomain *tail;

        assert(d);

        if (!d->marked)
                return;

        d->marked = false;

        if (!d->linked || !d->domains_next)
                return;

        switch (d->type) {

        case DNS_SEARCH_DOMAIN_LINK:
                assert(d->link);
                LIST_FIND_TAIL(domains, d, tail);
                LIST_REMOVE(domains, d->link->search_domains, d);
                LIST_INSERT_AFTER(domains, d->link->search_domains, tail, d);
                break;

        case DNS_SEARCH_DOMAIN_SYSTEM:
                LIST_FIND_TAIL(domains, d, tail);
                LIST_REMOVE(domains, d->manager->search_domains, d);
                LIST_INSERT_AFTER(domains, d->manager->search_domains, tail, d);
                break;

        default:
                assert_not_reached("Unknown search domain type");
        }
}