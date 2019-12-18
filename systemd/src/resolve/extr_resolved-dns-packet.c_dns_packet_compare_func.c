#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ DnsPacket ;

/* Variables and functions */
 int CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DNS_PACKET_DATA (TYPE_1__*) ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dns_packet_compare_func(const DnsPacket *x, const DnsPacket *y) {
        int r;

        r = CMP(x->size, y->size);
        if (r != 0)
                return r;

        return memcmp(DNS_PACKET_DATA((DnsPacket*) x), DNS_PACKET_DATA((DnsPacket*) y), x->size);
}