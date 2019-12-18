#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flags; int /*<<< orphan*/  question_idna; } ;
typedef  TYPE_1__ DnsScope ;
typedef  int /*<<< orphan*/  DnsQueryCandidate ;
typedef  TYPE_1__ DnsQuery ;

/* Variables and functions */
 int SD_RESOLVED_NO_SEARCH ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_query_candidate_free (int /*<<< orphan*/ *) ; 
 int dns_query_candidate_new (int /*<<< orphan*/ **,TYPE_1__*,TYPE_1__*) ; 
 int dns_query_candidate_next_search_domain (int /*<<< orphan*/ *) ; 
 int dns_query_candidate_setup_transactions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dns_question_first_name (int /*<<< orphan*/ ) ; 
 scalar_t__ dns_scope_name_needs_search_domain (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dns_query_add_candidate(DnsQuery *q, DnsScope *s) {
        DnsQueryCandidate *c;
        int r;

        assert(q);
        assert(s);

        r = dns_query_candidate_new(&c, q, s);
        if (r < 0)
                return r;

        /* If this a single-label domain on DNS, we might append a suitable search domain first. */
        if ((q->flags & SD_RESOLVED_NO_SEARCH) == 0 &&
            dns_scope_name_needs_search_domain(s, dns_question_first_name(q->question_idna))) {
                /* OK, we need a search domain now. Let's find one for this scope */

                r = dns_query_candidate_next_search_domain(c);
                if (r <= 0) /* if there's no search domain, then we won't add any transaction. */
                        goto fail;
        }

        r = dns_query_candidate_setup_transactions(c);
        if (r < 0)
                goto fail;

        return 0;

fail:
        dns_query_candidate_free(c);
        return r;
}