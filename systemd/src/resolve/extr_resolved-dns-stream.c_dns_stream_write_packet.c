#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  write_queue; } ;
typedef  TYPE_1__ DnsStream ;
typedef  TYPE_1__ DnsPacket ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_packet_ref (TYPE_1__*) ; 
 int dns_stream_update_io (TYPE_1__*) ; 
 int ordered_set_put (int /*<<< orphan*/ ,TYPE_1__*) ; 

int dns_stream_write_packet(DnsStream *s, DnsPacket *p) {
        int r;

        assert(s);
        assert(p);

        r = ordered_set_put(s->write_queue, p);
        if (r < 0)
                return r;

        dns_packet_ref(p);

        return dns_stream_update_io(s);
}