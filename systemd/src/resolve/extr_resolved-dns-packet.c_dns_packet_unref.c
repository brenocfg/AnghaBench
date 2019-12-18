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
struct TYPE_5__ {scalar_t__ n_ref; struct TYPE_5__* more; } ;
typedef  TYPE_1__ DnsPacket ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dns_packet_free (TYPE_1__*) ; 

DnsPacket *dns_packet_unref(DnsPacket *p) {
        if (!p)
                return NULL;

        assert(p->n_ref > 0);

        dns_packet_unref(p->more);

        if (p->n_ref == 1)
                dns_packet_free(p);
        else
                p->n_ref--;

        return NULL;
}