#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int state; int start_delay; int fd; int /*<<< orphan*/  ip_service_type; int /*<<< orphan*/  port; TYPE_1__* lease; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  last_addr; int /*<<< orphan*/  attempt; int /*<<< orphan*/  receive_message; int /*<<< orphan*/  timeout_resend; int /*<<< orphan*/  event_priority; struct TYPE_25__* event; } ;
typedef  TYPE_2__ sd_dhcp_client ;
struct TYPE_24__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_2__ DHCPMessage ;

/* Variables and functions */
 int CLAMP (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int ENOMSG ; 
 int FORMAT_TIMESPAN_MAX ; 
 int /*<<< orphan*/  IN_SET (int,int const,int const) ; 
 int /*<<< orphan*/  RESTART_AFTER_NAK_MAX_USEC ; 
 int /*<<< orphan*/  RESTART_AFTER_NAK_MIN_USEC ; 
 int SD_DHCP_CLIENT_EVENT_EXPIRED ; 
 int SD_DHCP_CLIENT_EVENT_IP_ACQUIRE ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int asynchronous_close (int) ; 
 int client_handle_ack (TYPE_2__*,TYPE_2__*,int) ; 
 int client_handle_forcerenew (TYPE_2__*,TYPE_2__*,int) ; 
 int client_handle_offer (TYPE_2__*,TYPE_2__*,int) ; 
 int client_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  client_initialize_io_events (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_notify (TYPE_2__*,int) ; 
 int /*<<< orphan*/  client_receive_message_udp ; 
 int client_set_lease_timeouts (TYPE_2__*) ; 
 int client_start_delayed (TYPE_2__*) ; 
 int /*<<< orphan*/  client_stop (TYPE_2__*,int) ; 
 int /*<<< orphan*/  client_timeout_resend ; 
 int client_timeout_t1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  clock_boottime_or_monotonic () ; 
 int dhcp_network_bind_udp_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int event_reset_time (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  event_source_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_timespan (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_dhcp_client (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int client_handle_message(sd_dhcp_client *client, DHCPMessage *message, int len) {
        DHCP_CLIENT_DONT_DESTROY(client);
        char time_string[FORMAT_TIMESPAN_MAX];
        int r = 0, notify_event = 0;

        assert(client);
        assert(client->event);
        assert(message);

        switch (client->state) {
        case DHCP_STATE_SELECTING:

                r = client_handle_offer(client, message, len);
                if (r >= 0) {

                        client->state = DHCP_STATE_REQUESTING;
                        client->attempt = 0;

                        r = event_reset_time(client->event, &client->timeout_resend,
                                             clock_boottime_or_monotonic(),
                                             0, 0,
                                             client_timeout_resend, client,
                                             client->event_priority, "dhcp4-resend-timer", true);
                        if (r < 0)
                                goto error;
                } else if (r == -ENOMSG)
                        /* invalid message, let's ignore it */
                        return 0;

                break;

        case DHCP_STATE_REBOOTING:
        case DHCP_STATE_REQUESTING:
        case DHCP_STATE_RENEWING:
        case DHCP_STATE_REBINDING:

                r = client_handle_ack(client, message, len);
                if (r >= 0) {
                        client->start_delay = 0;
                        (void) event_source_disable(client->timeout_resend);
                        client->receive_message =
                                sd_event_source_unref(client->receive_message);
                        client->fd = asynchronous_close(client->fd);

                        if (IN_SET(client->state, DHCP_STATE_REQUESTING,
                                   DHCP_STATE_REBOOTING))
                                notify_event = SD_DHCP_CLIENT_EVENT_IP_ACQUIRE;
                        else if (r != SD_DHCP_CLIENT_EVENT_IP_ACQUIRE)
                                notify_event = r;

                        client->state = DHCP_STATE_BOUND;
                        client->attempt = 0;

                        client->last_addr = client->lease->address;

                        r = client_set_lease_timeouts(client);
                        if (r < 0) {
                                log_dhcp_client(client, "could not set lease timeouts");
                                goto error;
                        }

                        r = dhcp_network_bind_udp_socket(client->ifindex, client->lease->address, client->port, client->ip_service_type);
                        if (r < 0) {
                                log_dhcp_client(client, "could not bind UDP socket");
                                goto error;
                        }

                        client->fd = r;

                        client_initialize_io_events(client, client_receive_message_udp);

                        if (notify_event) {
                                client_notify(client, notify_event);
                                if (client->state == DHCP_STATE_STOPPED)
                                        return 0;
                        }

                } else if (r == -EADDRNOTAVAIL) {
                        /* got a NAK, let's restart the client */
                        client_notify(client, SD_DHCP_CLIENT_EVENT_EXPIRED);

                        r = client_initialize(client);
                        if (r < 0)
                                goto error;

                        r = client_start_delayed(client);
                        if (r < 0)
                                goto error;

                        log_dhcp_client(client, "REBOOT in %s", format_timespan(time_string, FORMAT_TIMESPAN_MAX,
                                                                                client->start_delay, USEC_PER_SEC));

                        client->start_delay = CLAMP(client->start_delay * 2,
                                                    RESTART_AFTER_NAK_MIN_USEC, RESTART_AFTER_NAK_MAX_USEC);

                        return 0;
                } else if (r == -ENOMSG)
                        /* invalid message, let's ignore it */
                        return 0;

                break;

        case DHCP_STATE_BOUND:
                r = client_handle_forcerenew(client, message, len);
                if (r >= 0) {
                        r = client_timeout_t1(NULL, 0, client);
                        if (r < 0)
                                goto error;
                } else if (r == -ENOMSG)
                        /* invalid message, let's ignore it */
                        return 0;

                break;

        case DHCP_STATE_INIT:
        case DHCP_STATE_INIT_REBOOT:

                break;

        case DHCP_STATE_STOPPED:
                r = -EINVAL;
                goto error;
        }

error:
        if (r < 0)
                client_stop(client, r);

        return r;
}