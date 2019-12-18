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
struct TYPE_11__ {int /*<<< orphan*/  transactions_by_key; } ;
struct TYPE_10__ {scalar_t__ answer_source; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ DnsTransaction ;
typedef  TYPE_2__ DnsScope ;
typedef  TYPE_2__ DnsResourceKey ;

/* Variables and functions */
 scalar_t__ DNS_TRANSACTION_NETWORK ; 
 int /*<<< orphan*/  DNS_TRANSACTION_RCODE_FAILURE ; 
 int /*<<< orphan*/  DNS_TRANSACTION_SUCCESS ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 TYPE_1__* hashmap_get (int /*<<< orphan*/ ,TYPE_2__*) ; 

DnsTransaction *dns_scope_find_transaction(DnsScope *scope, DnsResourceKey *key, bool cache_ok) {
        DnsTransaction *t;

        assert(scope);
        assert(key);

        /* Try to find an ongoing transaction that is a equal to the
         * specified question */
        t = hashmap_get(scope->transactions_by_key, key);
        if (!t)
                return NULL;

        /* Refuse reusing transactions that completed based on cached
         * data instead of a real packet, if that's requested. */
        if (!cache_ok &&
            IN_SET(t->state, DNS_TRANSACTION_SUCCESS, DNS_TRANSACTION_RCODE_FAILURE) &&
            t->answer_source != DNS_TRANSACTION_NETWORK)
                return NULL;

        return t;
}