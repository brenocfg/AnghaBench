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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_6__ {int fd; int /*<<< orphan*/  port; int /*<<< orphan*/  arp_type; int /*<<< orphan*/  mac_addr_len; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  xid; int /*<<< orphan*/  link; int /*<<< orphan*/  ifindex; scalar_t__ attempt; int /*<<< orphan*/  state; int /*<<< orphan*/  receive_message; } ;
typedef  TYPE_1__ sd_dhcp_client ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP_CLIENT_DONT_DESTROY (TYPE_1__*) ; 
 int /*<<< orphan*/  DHCP_STATE_REBINDING ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int asynchronous_close (int) ; 
 int client_initialize_events (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_receive_message_raw ; 
 int /*<<< orphan*/  client_stop (TYPE_1__*,int) ; 
 int dhcp_network_bind_raw_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int client_timeout_t2(sd_event_source *s, uint64_t usec, void *userdata) {
        sd_dhcp_client *client = userdata;
        DHCP_CLIENT_DONT_DESTROY(client);
        int r;

        assert(client);

        client->receive_message = sd_event_source_unref(client->receive_message);
        client->fd = asynchronous_close(client->fd);

        client->state = DHCP_STATE_REBINDING;
        client->attempt = 0;

        r = dhcp_network_bind_raw_socket(client->ifindex, &client->link,
                                         client->xid, client->mac_addr,
                                         client->mac_addr_len, client->arp_type,
                                         client->port);
        if (r < 0) {
                client_stop(client, r);
                return 0;
        }
        client->fd = r;

        return client_initialize_events(client, client_receive_message_raw);
}