#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ state; int /*<<< orphan*/  block_gc; int /*<<< orphan*/  scope; } ;
typedef  TYPE_1__ DnsTransaction ;
typedef  TYPE_1__ DnsPacket ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_TRANSACTION_INVALID_REPLY ; 
 scalar_t__ DNS_TRANSACTION_PENDING ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ dns_packet_validate_reply (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_scope_check_conflicts (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dns_transaction_close_connection (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_transaction_complete (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_transaction_gc (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_transaction_process_reply (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 

__attribute__((used)) static int dns_transaction_on_stream_packet(DnsTransaction *t, DnsPacket *p) {
        assert(t);
        assert(p);

        dns_transaction_close_connection(t);

        if (dns_packet_validate_reply(p) <= 0) {
                log_debug("Invalid TCP reply packet.");
                dns_transaction_complete(t, DNS_TRANSACTION_INVALID_REPLY);
                return 0;
        }

        dns_scope_check_conflicts(t->scope, p);

        t->block_gc++;
        dns_transaction_process_reply(t, p);
        t->block_gc--;

        /* If the response wasn't useful, then complete the transition
         * now. After all, we are the worst feature set now with TCP
         * sockets, and there's really no point in retrying. */
        if (t->state == DNS_TRANSACTION_PENDING)
                dns_transaction_complete(t, DNS_TRANSACTION_INVALID_REPLY);
        else
                dns_transaction_gc(t);

        return 0;
}