#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  server; TYPE_1__* scope; } ;
struct TYPE_5__ {scalar_t__ protocol; } ;
typedef  TYPE_2__ DnsTransaction ;

/* Variables and functions */
 scalar_t__ DNS_PROTOCOL_DNS ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int dns_server_dnssec_supported (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dns_transaction_dnssec_supported(DnsTransaction *t) {
        assert(t);

        /* Checks whether our transaction's DNS server is assumed to be compatible with DNSSEC. Returns false as soon
         * as we changed our mind about a server, and now believe it is incompatible with DNSSEC. */

        if (t->scope->protocol != DNS_PROTOCOL_DNS)
                return false;

        /* If we have picked no server, then we are working from the cache or some other source, and DNSSEC might well
         * be supported, hence return true. */
        if (!t->server)
                return true;

        /* Note that we do not check the feature level actually used for the transaction but instead the feature level
         * the server is known to support currently, as the transaction feature level might be lower than what the
         * server actually supports, since we might have downgraded this transaction's feature level because we got a
         * SERVFAIL earlier and wanted to check whether downgrading fixes it. */

        return dns_server_dnssec_supported(t->server);
}