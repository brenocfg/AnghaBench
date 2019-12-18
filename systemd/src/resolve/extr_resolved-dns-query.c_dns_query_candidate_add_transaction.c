#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_1__* query; int /*<<< orphan*/  clamp_ttl; int /*<<< orphan*/  notify_query_candidates; int /*<<< orphan*/  transactions; int /*<<< orphan*/  notify_query_candidates_done; int /*<<< orphan*/  scope; } ;
struct TYPE_16__ {int /*<<< orphan*/  clamp_ttl; } ;
typedef  TYPE_2__ DnsTransaction ;
typedef  TYPE_2__ DnsResourceKey ;
typedef  TYPE_2__ DnsQueryCandidate ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 TYPE_2__* dns_scope_find_transaction (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  dns_transaction_gc (TYPE_2__*) ; 
 int dns_transaction_new (TYPE_2__**,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ set_contains (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int set_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int set_put (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int dns_query_candidate_add_transaction(DnsQueryCandidate *c, DnsResourceKey *key) {
        DnsTransaction *t;
        int r;

        assert(c);
        assert(key);

        t = dns_scope_find_transaction(c->scope, key, true);
        if (!t) {
                r = dns_transaction_new(&t, c->scope, key);
                if (r < 0)
                        return r;
        } else {
                if (set_contains(c->transactions, t))
                        return 0;
        }

        r = set_ensure_allocated(&c->transactions, NULL);
        if (r < 0)
                goto gc;

        r = set_ensure_allocated(&t->notify_query_candidates, NULL);
        if (r < 0)
                goto gc;

        r = set_ensure_allocated(&t->notify_query_candidates_done, NULL);
        if (r < 0)
                goto gc;

        r = set_put(t->notify_query_candidates, c);
        if (r < 0)
                goto gc;

        r = set_put(c->transactions, t);
        if (r < 0) {
                (void) set_remove(t->notify_query_candidates, c);
                goto gc;
        }

        t->clamp_ttl = c->query->clamp_ttl;
        return 1;

gc:
        dns_transaction_gc(t);
        return r;
}