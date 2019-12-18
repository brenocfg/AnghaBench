#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  notify_transactions_done; int /*<<< orphan*/  notify_transactions; int /*<<< orphan*/  dnssec_transactions; } ;
typedef  TYPE_1__ DnsTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_transaction_gc (TYPE_1__*) ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* set_steal_first (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dns_transaction_flush_dnssec_transactions(DnsTransaction *t) {
        DnsTransaction *z;

        assert(t);

        while ((z = set_steal_first(t->dnssec_transactions))) {
                set_remove(z->notify_transactions, t);
                set_remove(z->notify_transactions_done, t);
                dns_transaction_gc(z);
        }
}