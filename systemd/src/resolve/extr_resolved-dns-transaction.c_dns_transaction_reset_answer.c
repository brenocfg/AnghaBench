#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int answer_authenticated; scalar_t__ answer_errno; scalar_t__ answer_nsec_ttl; int /*<<< orphan*/  answer_source; int /*<<< orphan*/  answer_dnssec_result; scalar_t__ answer_rcode; int /*<<< orphan*/  answer; int /*<<< orphan*/  received; } ;
typedef  TYPE_1__ DnsTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  _DNSSEC_RESULT_INVALID ; 
 int /*<<< orphan*/  _DNS_TRANSACTION_SOURCE_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_answer_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_packet_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dns_transaction_reset_answer(DnsTransaction *t) {
        assert(t);

        t->received = dns_packet_unref(t->received);
        t->answer = dns_answer_unref(t->answer);
        t->answer_rcode = 0;
        t->answer_dnssec_result = _DNSSEC_RESULT_INVALID;
        t->answer_source = _DNS_TRANSACTION_SOURCE_INVALID;
        t->answer_authenticated = false;
        t->answer_nsec_ttl = (uint32_t) -1;
        t->answer_errno = 0;
}