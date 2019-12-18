#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* scope; TYPE_1__* query; int /*<<< orphan*/  search_domain; int /*<<< orphan*/  transactions; } ;
struct TYPE_11__ {int /*<<< orphan*/  query_candidates; } ;
struct TYPE_10__ {int /*<<< orphan*/  candidates; } ;
typedef  TYPE_3__ DnsQueryCandidate ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  candidates_by_query ; 
 int /*<<< orphan*/  candidates_by_scope ; 
 int /*<<< orphan*/  dns_query_candidate_stop (TYPE_3__*) ; 
 int /*<<< orphan*/  dns_search_domain_unref (int /*<<< orphan*/ ) ; 
 TYPE_3__* mfree (TYPE_3__*) ; 
 int /*<<< orphan*/  set_free (int /*<<< orphan*/ ) ; 

DnsQueryCandidate* dns_query_candidate_free(DnsQueryCandidate *c) {

        if (!c)
                return NULL;

        dns_query_candidate_stop(c);

        set_free(c->transactions);
        dns_search_domain_unref(c->search_domain);

        if (c->query)
                LIST_REMOVE(candidates_by_query, c->query->candidates, c);

        if (c->scope)
                LIST_REMOVE(candidates_by_scope, c->scope->query_candidates, c);

        return mfree(c);
}