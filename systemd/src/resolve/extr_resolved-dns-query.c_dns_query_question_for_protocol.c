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
struct TYPE_4__ {int /*<<< orphan*/ * question_utf8; int /*<<< orphan*/ * question_idna; } ;
typedef  int /*<<< orphan*/  DnsQuestion ;
typedef  TYPE_1__ DnsQuery ;
typedef  int DnsProtocol ;

/* Variables and functions */
#define  DNS_PROTOCOL_DNS 130 
#define  DNS_PROTOCOL_LLMNR 129 
#define  DNS_PROTOCOL_MDNS 128 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

DnsQuestion* dns_query_question_for_protocol(DnsQuery *q, DnsProtocol protocol) {
        assert(q);

        switch (protocol) {

        case DNS_PROTOCOL_DNS:
                return q->question_idna;

        case DNS_PROTOCOL_MDNS:
        case DNS_PROTOCOL_LLMNR:
                return q->question_utf8;

        default:
                return NULL;
        }
}