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
struct TYPE_7__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ DnsTransaction ;
typedef  TYPE_1__ DnsResourceRecord ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int dns_resource_key_match_cname_or_dname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dns_resource_key_match_rr (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dns_transaction_is_primary_response(DnsTransaction *t, DnsResourceRecord *rr) {
        int r;

        assert(t);
        assert(rr);

        /* Check if the specified RR is the "primary" response,
         * i.e. either matches the question precisely or is a
         * CNAME/DNAME for it. */

        r = dns_resource_key_match_rr(t->key, rr, NULL);
        if (r != 0)
                return r;

        return dns_resource_key_match_cname_or_dname(t->key, rr->key, NULL);
}