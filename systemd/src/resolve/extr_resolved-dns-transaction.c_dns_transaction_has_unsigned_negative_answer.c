#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  answer; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ DnsTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int dns_answer_contains_nsec_or_nsec3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_resource_key_name (int /*<<< orphan*/ ) ; 
 int dns_transaction_has_positive_answer (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int dns_transaction_negative_trust_anchor_lookup (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dns_transaction_has_unsigned_negative_answer(DnsTransaction *t) {
        int r;

        assert(t);

        /* Checks whether the answer is negative, and lacks NSEC/NSEC3
         * RRs to prove it */

        r = dns_transaction_has_positive_answer(t, NULL);
        if (r < 0)
                return r;
        if (r > 0)
                return false;

        /* Is this key explicitly listed as a negative trust anchor?
         * If so, it's nothing we need to care about */
        r = dns_transaction_negative_trust_anchor_lookup(t, dns_resource_key_name(t->key));
        if (r < 0)
                return r;
        if (r > 0)
                return false;

        /* The answer does not contain any RRs that match to the
         * question. If so, let's see if there are any NSEC/NSEC3 RRs
         * included. If not, the answer is unsigned. */

        r = dns_answer_contains_nsec_or_nsec3(t->answer);
        if (r < 0)
                return r;
        if (r > 0)
                return false;

        return true;
}