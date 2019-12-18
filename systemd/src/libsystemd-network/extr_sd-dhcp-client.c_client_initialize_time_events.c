#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {scalar_t__ start_delay; int /*<<< orphan*/  event_priority; int /*<<< orphan*/  timeout_resend; struct TYPE_8__* event; } ;
typedef  TYPE_1__ sd_dhcp_client ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  client_stop (TYPE_1__*,int) ; 
 int /*<<< orphan*/  client_timeout_resend ; 
 int /*<<< orphan*/  clock_boottime_or_monotonic () ; 
 int event_reset_time (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ sd_event_now (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int client_initialize_time_events(sd_dhcp_client *client) {
        uint64_t usec = 0;
        int r;

        assert(client);
        assert(client->event);

        if (client->start_delay > 0) {
                assert_se(sd_event_now(client->event, clock_boottime_or_monotonic(), &usec) >= 0);
                usec += client->start_delay;
        }

        r = event_reset_time(client->event, &client->timeout_resend,
                             clock_boottime_or_monotonic(),
                             usec, 0,
                             client_timeout_resend, client,
                             client->event_priority, "dhcp4-resend-timer", true);
        if (r < 0)
                client_stop(client, r);

        return 0;

}