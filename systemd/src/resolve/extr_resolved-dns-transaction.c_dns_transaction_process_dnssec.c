#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ dnssec_mode; } ;
struct TYPE_11__ {scalar_t__ answer_dnssec_result; scalar_t__ n_picked_servers; scalar_t__ answer_rcode; int answer_errno; int /*<<< orphan*/  server; TYPE_9__* scope; } ;
typedef  TYPE_1__ DnsTransaction ;

/* Variables and functions */
 scalar_t__ DNSSEC_INCOMPATIBLE_SERVER ; 
 int /*<<< orphan*/  DNSSEC_UNSIGNED ; 
 int /*<<< orphan*/  DNSSEC_VALIDATED ; 
 scalar_t__ DNSSEC_YES ; 
 scalar_t__ DNS_RCODE_SUCCESS ; 
 int /*<<< orphan*/  DNS_TRANSACTION_DNSSEC_FAILED ; 
 int /*<<< orphan*/  DNS_TRANSACTION_ERRNO ; 
 int /*<<< orphan*/  DNS_TRANSACTION_INVALID_REPLY ; 
 int /*<<< orphan*/  DNS_TRANSACTION_RCODE_FAILURE ; 
 int /*<<< orphan*/  DNS_TRANSACTION_SUCCESS ; 
 int EBADMSG ; 
 int /*<<< orphan*/  IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _DNSSEC_RESULT_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ dns_scope_get_n_dns_servers (TYPE_9__*) ; 
 int /*<<< orphan*/  dns_server_warn_downgrade (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_transaction_cache_answer (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_transaction_complete (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int dns_transaction_dnssec_ready (TYPE_1__*) ; 
 int dns_transaction_maybe_restart (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_transaction_retry (TYPE_1__*,int) ; 
 int dns_transaction_validate_dnssec (TYPE_1__*) ; 

__attribute__((used)) static void dns_transaction_process_dnssec(DnsTransaction *t) {
        int r;

        assert(t);

        /* Are there ongoing DNSSEC transactions? If so, let's wait for them. */
        r = dns_transaction_dnssec_ready(t);
        if (r < 0)
                goto fail;
        if (r == 0) /* We aren't ready yet (or one of our auxiliary transactions failed, and we shouldn't validate now */
                return;

        /* See if we learnt things from the additional DNSSEC transactions, that we didn't know before, and better
         * restart the lookup immediately. */
        r = dns_transaction_maybe_restart(t);
        if (r < 0)
                goto fail;
        if (r > 0) /* Transaction got restarted... */
                return;

        /* All our auxiliary DNSSEC transactions are complete now. Try
         * to validate our RRset now. */
        r = dns_transaction_validate_dnssec(t);
        if (r == -EBADMSG) {
                dns_transaction_complete(t, DNS_TRANSACTION_INVALID_REPLY);
                return;
        }
        if (r < 0)
                goto fail;

        if (t->answer_dnssec_result == DNSSEC_INCOMPATIBLE_SERVER &&
            t->scope->dnssec_mode == DNSSEC_YES) {

                /*  We are not in automatic downgrade mode, and the server is bad. Let's try a different server, maybe
                 *  that works. */

                if (t->n_picked_servers < dns_scope_get_n_dns_servers(t->scope)) {
                        /* We tried fewer servers on this transaction than we know, let's try another one then */
                        dns_transaction_retry(t, true);
                        return;
                }

                /* OK, let's give up, apparently all servers we tried didn't work. */
                dns_transaction_complete(t, DNS_TRANSACTION_DNSSEC_FAILED);
                return;
        }

        if (!IN_SET(t->answer_dnssec_result,
                    _DNSSEC_RESULT_INVALID,        /* No DNSSEC validation enabled */
                    DNSSEC_VALIDATED,              /* Answer is signed and validated successfully */
                    DNSSEC_UNSIGNED,               /* Answer is right-fully unsigned */
                    DNSSEC_INCOMPATIBLE_SERVER)) { /* Server does not do DNSSEC (Yay, we are downgrade attack vulnerable!) */
                dns_transaction_complete(t, DNS_TRANSACTION_DNSSEC_FAILED);
                return;
        }

        if (t->answer_dnssec_result == DNSSEC_INCOMPATIBLE_SERVER)
                dns_server_warn_downgrade(t->server);

        dns_transaction_cache_answer(t);

        if (t->answer_rcode == DNS_RCODE_SUCCESS)
                dns_transaction_complete(t, DNS_TRANSACTION_SUCCESS);
        else
                dns_transaction_complete(t, DNS_TRANSACTION_RCODE_FAILURE);

        return;

fail:
        t->answer_errno = -r;
        dns_transaction_complete(t, DNS_TRANSACTION_ERRNO);
}