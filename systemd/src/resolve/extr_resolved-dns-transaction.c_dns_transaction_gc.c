#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ block_gc; int /*<<< orphan*/  notify_transactions_done; int /*<<< orphan*/  notify_transactions; int /*<<< orphan*/  notify_zone_items_done; int /*<<< orphan*/  notify_zone_items; int /*<<< orphan*/  notify_query_candidates_done; int /*<<< orphan*/  notify_query_candidates; } ;
typedef  TYPE_1__ DnsTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_transaction_free (TYPE_1__*) ; 
 scalar_t__ set_isempty (int /*<<< orphan*/ ) ; 

bool dns_transaction_gc(DnsTransaction *t) {
        assert(t);

        if (t->block_gc > 0)
                return true;

        if (set_isempty(t->notify_query_candidates) &&
            set_isempty(t->notify_query_candidates_done) &&
            set_isempty(t->notify_zone_items) &&
            set_isempty(t->notify_zone_items_done) &&
            set_isempty(t->notify_transactions) &&
            set_isempty(t->notify_transactions_done)) {
                dns_transaction_free(t);
                return false;
        }

        return true;
}