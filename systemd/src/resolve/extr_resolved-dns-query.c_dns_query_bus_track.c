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
struct TYPE_9__ {int /*<<< orphan*/  bus_track; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  TYPE_1__ DnsQuery ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  on_bus_track ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (TYPE_1__*) ; 
 int sd_bus_track_add_sender (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sd_bus_track_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

int dns_query_bus_track(DnsQuery *q, sd_bus_message *m) {
        int r;

        assert(q);
        assert(m);

        if (!q->bus_track) {
                r = sd_bus_track_new(sd_bus_message_get_bus(m), &q->bus_track, on_bus_track, q);
                if (r < 0)
                        return r;
        }

        r = sd_bus_track_add_sender(q->bus_track, m);
        if (r < 0)
                return r;

        return 0;
}