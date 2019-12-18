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
struct TYPE_5__ {scalar_t__ answer_rcode; } ;
typedef  TYPE_1__ DnsTransaction ;

/* Variables and functions */
 scalar_t__ DNS_RCODE_NXDOMAIN ; 
 scalar_t__ DNS_RCODE_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int dns_transaction_has_positive_answer (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dns_transaction_fix_rcode(DnsTransaction *t) {
        int r;

        assert(t);

        /* Fix up the RCODE to SUCCESS if we get at least one matching RR in a response. Note that this contradicts the
         * DNS RFCs a bit. Specifically, RFC 6604 Section 3 clarifies that the RCODE shall say something about a
         * CNAME/DNAME chain element coming after the last chain element contained in the message, and not the first
         * one included. However, it also indicates that not all DNS servers implement this correctly. Moreover, when
         * using DNSSEC we usually only can prove the first element of a CNAME/DNAME chain anyway, hence let's settle
         * on always processing the RCODE as referring to the immediate look-up we do, i.e. the first element of a
         * CNAME/DNAME chain. This way, we uniformly handle CNAME/DNAME chains, regardless if the DNS server
         * incorrectly implements RCODE, whether DNSSEC is in use, or whether the DNS server only supplied us with an
         * incomplete CNAME/DNAME chain.
         *
         * Or in other words: if we get at least one positive reply in a message we patch NXDOMAIN to become SUCCESS,
         * and then rely on the CNAME chasing logic to figure out that there's actually a CNAME error with a new
         * lookup. */

        if (t->answer_rcode != DNS_RCODE_NXDOMAIN)
                return 0;

        r = dns_transaction_has_positive_answer(t, NULL);
        if (r <= 0)
                return r;

        t->answer_rcode = DNS_RCODE_SUCCESS;
        return 0;
}