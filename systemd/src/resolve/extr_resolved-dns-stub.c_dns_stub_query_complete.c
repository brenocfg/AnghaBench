#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int state; struct TYPE_12__* request_dns_packet; int /*<<< orphan*/  request_dns_stream; int /*<<< orphan*/  manager; int /*<<< orphan*/  answer_rcode; int /*<<< orphan*/  reply_dns_packet; int /*<<< orphan*/  opt; int /*<<< orphan*/  answer; int /*<<< orphan*/  question_idna; } ;
typedef  TYPE_1__ DnsQuery ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_PACKET_DO (TYPE_1__*) ; 
 int /*<<< orphan*/  DNS_PACKET_ID (TYPE_1__*) ; 
 int /*<<< orphan*/  DNS_PACKET_PAYLOAD_SIZE_MAX (TYPE_1__*) ; 
 int DNS_QUERY_RESTARTED ; 
 int /*<<< orphan*/  DNS_RCODE_NXDOMAIN ; 
 int /*<<< orphan*/  DNS_RCODE_SERVFAIL ; 
#define  DNS_TRANSACTION_ABORTED 143 
#define  DNS_TRANSACTION_ATTEMPTS_MAX_REACHED 142 
#define  DNS_TRANSACTION_DNSSEC_FAILED 141 
#define  DNS_TRANSACTION_ERRNO 140 
#define  DNS_TRANSACTION_INVALID_REPLY 139 
#define  DNS_TRANSACTION_NETWORK_DOWN 138 
#define  DNS_TRANSACTION_NOT_FOUND 137 
#define  DNS_TRANSACTION_NO_SERVERS 136 
#define  DNS_TRANSACTION_NO_TRUST_ANCHOR 135 
#define  DNS_TRANSACTION_NULL 134 
#define  DNS_TRANSACTION_PENDING 133 
#define  DNS_TRANSACTION_RCODE_FAILURE 132 
#define  DNS_TRANSACTION_RR_TYPE_UNSUPPORTED 131 
#define  DNS_TRANSACTION_SUCCESS 130 
#define  DNS_TRANSACTION_TIMEOUT 129 
#define  DNS_TRANSACTION_VALIDATING 128 
 int ELOOP ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  dns_query_free (TYPE_1__*) ; 
 int dns_query_fully_authenticated (TYPE_1__*) ; 
 int dns_query_process_cname (TYPE_1__*) ; 
 int dns_stub_finish_reply_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int dns_stub_make_reply_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dns_stub_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_stub_send_failure (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*) ; 

__attribute__((used)) static void dns_stub_query_complete(DnsQuery *q) {
        int r;

        assert(q);
        assert(q->request_dns_packet);

        switch (q->state) {

        case DNS_TRANSACTION_SUCCESS: {
                bool truncated;

                r = dns_stub_make_reply_packet(&q->reply_dns_packet, DNS_PACKET_PAYLOAD_SIZE_MAX(q->request_dns_packet), q->question_idna, q->answer, &truncated);
                if (r < 0) {
                        log_debug_errno(r, "Failed to build reply packet: %m");
                        break;
                }

                if (!truncated) {
                        r = dns_query_process_cname(q);
                        if (r == -ELOOP) {
                                (void) dns_stub_send_failure(q->manager, q->request_dns_stream, q->request_dns_packet, DNS_RCODE_SERVFAIL, false);
                                break;
                        }
                        if (r < 0) {
                                log_debug_errno(r, "Failed to process CNAME: %m");
                                break;
                        }
                        if (r == DNS_QUERY_RESTARTED)
                                return;
                }

                r = dns_stub_finish_reply_packet(
                                q->reply_dns_packet,
                                DNS_PACKET_ID(q->request_dns_packet),
                                q->answer_rcode,
                                truncated,
                                !!q->request_dns_packet->opt,
                                DNS_PACKET_DO(q->request_dns_packet),
                                dns_query_fully_authenticated(q));
                if (r < 0) {
                        log_debug_errno(r, "Failed to finish reply packet: %m");
                        break;
                }

                (void) dns_stub_send(q->manager, q->request_dns_stream, q->request_dns_packet, q->reply_dns_packet);
                break;
        }

        case DNS_TRANSACTION_RCODE_FAILURE:
                (void) dns_stub_send_failure(q->manager, q->request_dns_stream, q->request_dns_packet, q->answer_rcode, dns_query_fully_authenticated(q));
                break;

        case DNS_TRANSACTION_NOT_FOUND:
                (void) dns_stub_send_failure(q->manager, q->request_dns_stream, q->request_dns_packet, DNS_RCODE_NXDOMAIN, dns_query_fully_authenticated(q));
                break;

        case DNS_TRANSACTION_TIMEOUT:
        case DNS_TRANSACTION_ATTEMPTS_MAX_REACHED:
                /* Propagate a timeout as a no packet, i.e. that the client also gets a timeout */
                break;

        case DNS_TRANSACTION_NO_SERVERS:
        case DNS_TRANSACTION_INVALID_REPLY:
        case DNS_TRANSACTION_ERRNO:
        case DNS_TRANSACTION_ABORTED:
        case DNS_TRANSACTION_DNSSEC_FAILED:
        case DNS_TRANSACTION_NO_TRUST_ANCHOR:
        case DNS_TRANSACTION_RR_TYPE_UNSUPPORTED:
        case DNS_TRANSACTION_NETWORK_DOWN:
                (void) dns_stub_send_failure(q->manager, q->request_dns_stream, q->request_dns_packet, DNS_RCODE_SERVFAIL, false);
                break;

        case DNS_TRANSACTION_NULL:
        case DNS_TRANSACTION_PENDING:
        case DNS_TRANSACTION_VALIDATING:
        default:
                assert_not_reached("Impossible state");
        }

        dns_query_free(q);
}