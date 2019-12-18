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
struct TYPE_4__ {int n_read; int /*<<< orphan*/  read_packet; int /*<<< orphan*/  read_size; } ;
typedef  TYPE_1__ DnsStream ;
typedef  int /*<<< orphan*/  DnsPacket ;

/* Variables and functions */
 int /*<<< orphan*/ * TAKE_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int be16toh (int /*<<< orphan*/ ) ; 

DnsPacket *dns_stream_take_read_packet(DnsStream *s) {
        assert(s);

        if (!s->read_packet)
                return NULL;

        if (s->n_read < sizeof(s->read_size))
                return NULL;

        if (s->n_read < sizeof(s->read_size) + be16toh(s->read_size))
                return NULL;

        s->n_read = 0;
        return TAKE_PTR(s->read_packet);
}