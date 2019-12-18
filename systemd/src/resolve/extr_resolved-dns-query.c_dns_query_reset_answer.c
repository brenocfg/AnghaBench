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
struct TYPE_4__ {int answer_authenticated; int /*<<< orphan*/  answer_search_domain; int /*<<< orphan*/  answer_family; int /*<<< orphan*/  answer_protocol; scalar_t__ answer_errno; int /*<<< orphan*/  answer_dnssec_result; scalar_t__ answer_rcode; int /*<<< orphan*/  answer; } ;
typedef  TYPE_1__ DnsQuery ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  _DNSSEC_RESULT_INVALID ; 
 int /*<<< orphan*/  _DNS_PROTOCOL_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_answer_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_search_domain_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dns_query_reset_answer(DnsQuery *q) {
        assert(q);

        q->answer = dns_answer_unref(q->answer);
        q->answer_rcode = 0;
        q->answer_dnssec_result = _DNSSEC_RESULT_INVALID;
        q->answer_errno = 0;
        q->answer_authenticated = false;
        q->answer_protocol = _DNS_PROTOCOL_INVALID;
        q->answer_family = AF_UNSPEC;
        q->answer_search_domain = dns_search_domain_unref(q->answer_search_domain);
}