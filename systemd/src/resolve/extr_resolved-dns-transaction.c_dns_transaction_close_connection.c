#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  write_queue; int /*<<< orphan*/  transactions; } ;
struct TYPE_7__ {int /*<<< orphan*/  dns_udp_fd; int /*<<< orphan*/  dns_udp_event_source; TYPE_3__* stream; int /*<<< orphan*/  sent; } ;
typedef  TYPE_1__ DnsTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_packet_unref (int /*<<< orphan*/ ) ; 
 TYPE_3__* dns_stream_unref (TYPE_3__*) ; 
 int /*<<< orphan*/  ordered_set_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transactions_by_stream ; 

__attribute__((used)) static void dns_transaction_close_connection(DnsTransaction *t) {
        assert(t);

        if (t->stream) {
                /* Let's detach the stream from our transaction, in case something else keeps a reference to it. */
                LIST_REMOVE(transactions_by_stream, t->stream->transactions, t);

                /* Remove packet in case it's still in the queue */
                dns_packet_unref(ordered_set_remove(t->stream->write_queue, t->sent));

                t->stream = dns_stream_unref(t->stream);
        }

        t->dns_udp_event_source = sd_event_source_unref(t->dns_udp_event_source);
        t->dns_udp_fd = safe_close(t->dns_udp_fd);
}