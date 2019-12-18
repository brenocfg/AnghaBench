#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int protocol; } ;
typedef  TYPE_1__ DnsPacket ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_PACKET_AA (TYPE_1__*) ; 
 int /*<<< orphan*/  DNS_PACKET_AD (TYPE_1__*) ; 
 int /*<<< orphan*/  DNS_PACKET_ANCOUNT (TYPE_1__*) ; 
 int /*<<< orphan*/  DNS_PACKET_CD (TYPE_1__*) ; 
 int /*<<< orphan*/  DNS_PACKET_NSCOUNT (TYPE_1__*) ; 
 scalar_t__ DNS_PACKET_OPCODE (TYPE_1__*) ; 
 int DNS_PACKET_QDCOUNT (TYPE_1__*) ; 
 scalar_t__ DNS_PACKET_QR (TYPE_1__*) ; 
 int /*<<< orphan*/  DNS_PACKET_RA (TYPE_1__*) ; 
 int /*<<< orphan*/  DNS_PACKET_RCODE (TYPE_1__*) ; 
 int /*<<< orphan*/  DNS_PACKET_RD (TYPE_1__*) ; 
 scalar_t__ DNS_PACKET_TC (TYPE_1__*) ; 
#define  DNS_PROTOCOL_DNS 130 
#define  DNS_PROTOCOL_LLMNR 129 
#define  DNS_PROTOCOL_MDNS 128 
 int EBADMSG ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int dns_packet_validate (TYPE_1__*) ; 

int dns_packet_validate_query(DnsPacket *p) {
        int r;

        assert(p);

        r = dns_packet_validate(p);
        if (r < 0)
                return r;

        if (DNS_PACKET_QR(p) != 0)
                return 0;

        if (DNS_PACKET_OPCODE(p) != 0)
                return -EBADMSG;

        if (DNS_PACKET_TC(p))
                return -EBADMSG;

        switch (p->protocol) {

        case DNS_PROTOCOL_LLMNR:
        case DNS_PROTOCOL_DNS:
                /* RFC 4795, Section 2.1.1. says to discard all queries with QDCOUNT != 1 */
                if (DNS_PACKET_QDCOUNT(p) != 1)
                        return -EBADMSG;

                /* RFC 4795, Section 2.1.1. says to discard all queries with ANCOUNT != 0 */
                if (DNS_PACKET_ANCOUNT(p) > 0)
                        return -EBADMSG;

                /* RFC 4795, Section 2.1.1. says to discard all queries with NSCOUNT != 0 */
                if (DNS_PACKET_NSCOUNT(p) > 0)
                        return -EBADMSG;

                break;

        case DNS_PROTOCOL_MDNS:
                /* RFC 6762, Section 18 */
                if (DNS_PACKET_AA(p)    != 0 ||
                    DNS_PACKET_RD(p)    != 0 ||
                    DNS_PACKET_RA(p)    != 0 ||
                    DNS_PACKET_AD(p)    != 0 ||
                    DNS_PACKET_CD(p)    != 0 ||
                    DNS_PACKET_RCODE(p) != 0)
                        return -EBADMSG;

                break;

        default:
                break;
        }

        return 1;
}