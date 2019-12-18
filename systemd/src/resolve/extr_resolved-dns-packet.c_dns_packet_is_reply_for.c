#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* question; } ;
struct TYPE_10__ {int n_keys; int /*<<< orphan*/ * keys; } ;
typedef  TYPE_2__ DnsResourceKey ;
typedef  TYPE_2__ const DnsPacket ;

/* Variables and functions */
 int DNS_PACKET_QR (TYPE_2__ const*) ; 
 int /*<<< orphan*/  assert (TYPE_2__ const*) ; 
 int dns_packet_extract (TYPE_2__ const*) ; 
 int dns_resource_key_equal (int /*<<< orphan*/ ,TYPE_2__ const*) ; 

int dns_packet_is_reply_for(DnsPacket *p, const DnsResourceKey *key) {
        int r;

        assert(p);
        assert(key);

        /* Checks if the specified packet is a reply for the specified
         * key and the specified key is the only one in the question
         * section. */

        if (DNS_PACKET_QR(p) != 1)
                return 0;

        /* Let's unpack the packet, if that hasn't happened yet. */
        r = dns_packet_extract(p);
        if (r < 0)
                return r;

        if (!p->question)
                return 0;

        if (p->question->n_keys != 1)
                return 0;

        return dns_resource_key_equal(p->question->keys[0], key);
}