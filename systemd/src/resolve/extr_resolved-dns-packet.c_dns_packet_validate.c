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
struct TYPE_4__ {scalar_t__ size; } ;
typedef  TYPE_1__ DnsPacket ;

/* Variables and functions */
 scalar_t__ DNS_PACKET_HEADER_SIZE ; 
 scalar_t__ DNS_PACKET_SIZE_MAX ; 
 int EBADMSG ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

int dns_packet_validate(DnsPacket *p) {
        assert(p);

        if (p->size < DNS_PACKET_HEADER_SIZE)
                return -EBADMSG;

        if (p->size > DNS_PACKET_SIZE_MAX)
                return -EBADMSG;

        return 1;
}