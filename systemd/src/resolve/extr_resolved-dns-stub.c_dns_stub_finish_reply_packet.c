#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  DnsPacket ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISE_DATAGRAM_SIZE_MAX ; 
 TYPE_1__* DNS_PACKET_HEADER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DNS_PACKET_MAKE_FLAGS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int) ; 
 int DNS_RCODE_SERVFAIL ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int dns_packet_append_opt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htobe16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dns_stub_finish_reply_packet(
                DnsPacket *p,
                uint16_t id,
                int rcode,
                bool tc,        /* set the Truncated bit? */
                bool add_opt,   /* add an OPT RR to this packet? */
                bool edns0_do,  /* set the EDNS0 DNSSEC OK bit? */
                bool ad) {      /* set the DNSSEC authenticated data bit? */

        int r;

        assert(p);

        if (add_opt) {
                r = dns_packet_append_opt(p, ADVERTISE_DATAGRAM_SIZE_MAX, edns0_do, rcode, NULL);
                if (r == -EMSGSIZE) /* Hit the size limit? then indicate truncation */
                        tc = true;
                else if (r < 0)
                        return r;

        } else {
                /* If the client can't to EDNS0, don't do DO either */
                edns0_do = false;

                /* If the client didn't do EDNS, clamp the rcode to 4 bit */
                if (rcode > 0xF)
                        rcode = DNS_RCODE_SERVFAIL;
        }

        /* Don't set the AD bit unless DO is on, too */
        if (!edns0_do)
                ad = false;

        DNS_PACKET_HEADER(p)->id = id;

        DNS_PACKET_HEADER(p)->flags = htobe16(DNS_PACKET_MAKE_FLAGS(
                                                              1  /* qr */,
                                                              0  /* opcode */,
                                                              0  /* aa */,
                                                              tc /* tc */,
                                                              1  /* rd */,
                                                              1  /* ra */,
                                                              ad /* ad */,
                                                              0  /* cd */,
                                                              rcode));

        return 0;
}