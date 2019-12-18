#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  DnsPacket ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int dns_packet_read (int /*<<< orphan*/ *,int,void const**,size_t*) ; 
 int /*<<< orphan*/  unaligned_read_be16 (void const*) ; 

int dns_packet_read_uint16(DnsPacket *p, uint16_t *ret, size_t *start) {
        const void *d;
        int r;

        assert(p);

        r = dns_packet_read(p, sizeof(uint16_t), &d, start);
        if (r < 0)
                return r;

        *ret = unaligned_read_be16(d);

        return 0;
}