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
struct TYPE_6__ {scalar_t__ current_feature_level; int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ DnsTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ dns_server_possible_feature_level (int /*<<< orphan*/ ) ; 
 int dns_transaction_go (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_transaction_shuffle_id (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 

__attribute__((used)) static int dns_transaction_maybe_restart(DnsTransaction *t) {
        int r;

        assert(t);

        /* Returns > 0 if the transaction was restarted, 0 if not */

        if (!t->server)
                return 0;

        if (t->current_feature_level <= dns_server_possible_feature_level(t->server))
                return 0;

        /* The server's current feature level is lower than when we sent the original query. We learnt something from
           the response or possibly an auxiliary DNSSEC response that we didn't know before.  We take that as reason to
           restart the whole transaction. This is a good idea to deal with servers that respond rubbish if we include
           OPT RR or DO bit. One of these cases is documented here, for example:
           https://open.nlnetlabs.nl/pipermail/dnssec-trigger/2014-November/000376.html */

        log_debug("Server feature level is now lower than when we began our transaction. Restarting with new ID.");
        dns_transaction_shuffle_id(t);

        r = dns_transaction_go(t);
        if (r < 0)
                return r;

        return 1;
}