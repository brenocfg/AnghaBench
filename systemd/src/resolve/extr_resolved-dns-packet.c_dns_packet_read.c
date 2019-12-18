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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {size_t rindex; size_t size; } ;
typedef  TYPE_1__ DnsPacket ;

/* Variables and functions */
 scalar_t__ DNS_PACKET_DATA (TYPE_1__*) ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

int dns_packet_read(DnsPacket *p, size_t sz, const void **ret, size_t *start) {
        assert(p);

        if (p->rindex + sz > p->size)
                return -EMSGSIZE;

        if (ret)
                *ret = (uint8_t*) DNS_PACKET_DATA(p) + p->rindex;

        if (start)
                *start = p->rindex;

        p->rindex += sz;
        return 0;
}