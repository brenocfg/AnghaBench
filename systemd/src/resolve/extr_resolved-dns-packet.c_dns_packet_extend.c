#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {size_t size; size_t allocated; void* _data; } ;
typedef  TYPE_1__ DnsPacket ;

/* Variables and functions */
 int ALIGN (int) ; 
 scalar_t__ DNS_PACKET_DATA (TYPE_1__*) ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 size_t PAGE_ALIGN (size_t) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 size_t dns_packet_size_max (TYPE_1__*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memzero (int /*<<< orphan*/ *,size_t) ; 
 void* realloc (void*,size_t) ; 

__attribute__((used)) static int dns_packet_extend(DnsPacket *p, size_t add, void **ret, size_t *start) {
        assert(p);

        if (p->size + add > p->allocated) {
                size_t a, ms;

                a = PAGE_ALIGN((p->size + add) * 2);

                ms = dns_packet_size_max(p);
                if (a > ms)
                        a = ms;

                if (p->size + add > a)
                        return -EMSGSIZE;

                if (p->_data) {
                        void *d;

                        d = realloc(p->_data, a);
                        if (!d)
                                return -ENOMEM;

                        p->_data = d;
                } else {
                        p->_data = malloc(a);
                        if (!p->_data)
                                return -ENOMEM;

                        memcpy(p->_data, (uint8_t*) p + ALIGN(sizeof(DnsPacket)), p->size);
                        memzero((uint8_t*) p->_data + p->size, a - p->size);
                }

                p->allocated = a;
        }

        if (start)
                *start = p->size;

        if (ret)
                *ret = (uint8_t*) DNS_PACKET_DATA(p) + p->size;

        p->size += add;
        return 0;
}