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
struct TYPE_4__ {int /*<<< orphan*/  lease; scalar_t__ xid; int /*<<< orphan*/  state; scalar_t__ attempt; int /*<<< orphan*/  timeout_expire; int /*<<< orphan*/  timeout_t2; int /*<<< orphan*/  timeout_t1; int /*<<< orphan*/  timeout_resend; int /*<<< orphan*/  fd; int /*<<< orphan*/  receive_message; } ;
typedef  TYPE_1__ sd_dhcp_client ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP_STATE_INIT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asynchronous_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_source_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_dhcp_lease_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int client_initialize(sd_dhcp_client *client) {
        assert_return(client, -EINVAL);

        client->receive_message = sd_event_source_unref(client->receive_message);

        client->fd = asynchronous_close(client->fd);

        (void) event_source_disable(client->timeout_resend);
        (void) event_source_disable(client->timeout_t1);
        (void) event_source_disable(client->timeout_t2);
        (void) event_source_disable(client->timeout_expire);

        client->attempt = 0;

        client->state = DHCP_STATE_INIT;
        client->xid = 0;

        client->lease = sd_dhcp_lease_unref(client->lease);

        return 0;
}