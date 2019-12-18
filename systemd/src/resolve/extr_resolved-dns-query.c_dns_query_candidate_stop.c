#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  transactions; } ;
struct TYPE_8__ {int /*<<< orphan*/  notify_query_candidates_done; int /*<<< orphan*/  notify_query_candidates; } ;
typedef  TYPE_1__ DnsTransaction ;
typedef  TYPE_2__ DnsQueryCandidate ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  dns_transaction_gc (TYPE_1__*) ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* set_steal_first (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dns_query_candidate_stop(DnsQueryCandidate *c) {
        DnsTransaction *t;

        assert(c);

        while ((t = set_steal_first(c->transactions))) {
                set_remove(t->notify_query_candidates, c);
                set_remove(t->notify_query_candidates_done, c);
                dns_transaction_gc(t);
        }
}