#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int answer_errno; TYPE_1__* scope; } ;
struct TYPE_8__ {scalar_t__ protocol; } ;
typedef  TYPE_2__ DnsTransaction ;

/* Variables and functions */
 scalar_t__ DNS_PROTOCOL_LLMNR ; 
 int /*<<< orphan*/  DNS_TRANSACTION_ERRNO ; 
 int /*<<< orphan*/  DNS_TRANSACTION_NOT_FOUND ; 
 scalar_t__ ERRNO_IS_DISCONNECT (int) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  dns_transaction_close_connection (TYPE_2__*) ; 
 int /*<<< orphan*/  dns_transaction_complete (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_transaction_retry (TYPE_2__*,int) ; 

__attribute__((used)) static void on_transaction_stream_error(DnsTransaction *t, int error) {
        assert(t);

        dns_transaction_close_connection(t);

        if (ERRNO_IS_DISCONNECT(error)) {
                if (t->scope->protocol == DNS_PROTOCOL_LLMNR) {
                        /* If the LLMNR/TCP connection failed, the host doesn't support LLMNR, and we cannot answer the
                         * question on this scope. */
                        dns_transaction_complete(t, DNS_TRANSACTION_NOT_FOUND);
                        return;
                }

                dns_transaction_retry(t, true);
                return;
        }
        if (error != 0) {
                t->answer_errno = error;
                dns_transaction_complete(t, DNS_TRANSACTION_ERRNO);
        }
}