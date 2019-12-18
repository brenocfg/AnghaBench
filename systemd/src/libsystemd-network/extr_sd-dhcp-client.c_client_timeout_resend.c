#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int usec_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_18__ {int state; int request_sent; int /*<<< orphan*/  max_attempts; int /*<<< orphan*/  attempt; int /*<<< orphan*/  event_priority; int /*<<< orphan*/  timeout_resend; struct TYPE_18__* event; TYPE_1__* lease; } ;
typedef  TYPE_2__ sd_event_source ;
typedef  TYPE_2__ sd_dhcp_client ;
struct TYPE_17__ {int t2; int t1; int lifetime; } ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP_CLIENT_DONT_DESTROY (TYPE_2__*) ; 
#define  DHCP_STATE_BOUND 136 
#define  DHCP_STATE_INIT 135 
#define  DHCP_STATE_INIT_REBOOT 134 
#define  DHCP_STATE_REBINDING 133 
#define  DHCP_STATE_REBOOTING 132 
#define  DHCP_STATE_RENEWING 131 
#define  DHCP_STATE_REQUESTING 130 
#define  DHCP_STATE_SELECTING 129 
#define  DHCP_STATE_STOPPED 128 
 int EINVAL ; 
 int MIN (int /*<<< orphan*/ ,int) ; 
 int UINT64_C (int) ; 
 int USEC_PER_MSEC ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int client_initialize (TYPE_2__*) ; 
 int client_send_discover (TYPE_2__*) ; 
 int client_send_request (TYPE_2__*) ; 
 int client_start (TYPE_2__*) ; 
 int /*<<< orphan*/  client_stop (TYPE_2__*,int) ; 
 int /*<<< orphan*/  clock_boottime_or_monotonic () ; 
 int event_reset_time (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int (*) (TYPE_2__*,int,void*),TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  log_dhcp_client (TYPE_2__*,char*) ; 
 int random_u32 () ; 
 int sd_event_now (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int client_timeout_resend(
                sd_event_source *s,
                uint64_t usec,
                void *userdata) {

        sd_dhcp_client *client = userdata;
        DHCP_CLIENT_DONT_DESTROY(client);
        usec_t next_timeout = 0;
        uint64_t time_now;
        uint32_t time_left;
        int r;

        assert(s);
        assert(client);
        assert(client->event);

        r = sd_event_now(client->event, clock_boottime_or_monotonic(), &time_now);
        if (r < 0)
                goto error;

        switch (client->state) {

        case DHCP_STATE_RENEWING:

                time_left = (client->lease->t2 - client->lease->t1) / 2;
                if (time_left < 60)
                        time_left = 60;

                next_timeout = time_now + time_left * USEC_PER_SEC;

                break;

        case DHCP_STATE_REBINDING:

                time_left = (client->lease->lifetime - client->lease->t2) / 2;
                if (time_left < 60)
                        time_left = 60;

                next_timeout = time_now + time_left * USEC_PER_SEC;
                break;

        case DHCP_STATE_REBOOTING:
                /* start over as we did not receive a timely ack or nak */
                r = client_initialize(client);
                if (r < 0)
                        goto error;

                r = client_start(client);
                if (r < 0)
                        goto error;
                else {
                        log_dhcp_client(client, "REBOOTED");
                        return 0;
                }

        case DHCP_STATE_INIT:
        case DHCP_STATE_INIT_REBOOT:
        case DHCP_STATE_SELECTING:
        case DHCP_STATE_REQUESTING:
        case DHCP_STATE_BOUND:

                if (client->attempt < client->max_attempts)
                        client->attempt++;
                else
                        goto error;

                next_timeout = time_now + ((UINT64_C(1) << MIN(client->attempt, (uint64_t) 6)) - 1) * USEC_PER_SEC;

                break;

        case DHCP_STATE_STOPPED:
                r = -EINVAL;
                goto error;
        }

        next_timeout += (random_u32() & 0x1fffff);

        r = event_reset_time(client->event, &client->timeout_resend,
                             clock_boottime_or_monotonic(),
                             next_timeout, 10 * USEC_PER_MSEC,
                             client_timeout_resend, client,
                             client->event_priority, "dhcp4-resend-timer", true);
        if (r < 0)
                goto error;

        switch (client->state) {
        case DHCP_STATE_INIT:
                r = client_send_discover(client);
                if (r >= 0) {
                        client->state = DHCP_STATE_SELECTING;
                        client->attempt = 0;
                } else if (client->attempt >= client->max_attempts)
                        goto error;

                break;

        case DHCP_STATE_SELECTING:
                r = client_send_discover(client);
                if (r < 0 && client->attempt >= client->max_attempts)
                        goto error;

                break;

        case DHCP_STATE_INIT_REBOOT:
        case DHCP_STATE_REQUESTING:
        case DHCP_STATE_RENEWING:
        case DHCP_STATE_REBINDING:
                r = client_send_request(client);
                if (r < 0 && client->attempt >= client->max_attempts)
                         goto error;

                if (client->state == DHCP_STATE_INIT_REBOOT)
                        client->state = DHCP_STATE_REBOOTING;

                client->request_sent = time_now;

                break;

        case DHCP_STATE_REBOOTING:
        case DHCP_STATE_BOUND:

                break;

        case DHCP_STATE_STOPPED:
                r = -EINVAL;
                goto error;
        }

        return 0;

error:
        client_stop(client, r);

        /* Errors were dealt with when stopping the client, don't spill
           errors into the event loop handler */
        return 0;
}