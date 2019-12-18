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
struct TYPE_4__ {int /*<<< orphan*/  state; int /*<<< orphan*/  timeout_t2; int /*<<< orphan*/  timeout_t1; int /*<<< orphan*/  timeout_resend_expire; int /*<<< orphan*/  timeout_resend; scalar_t__ retransmit_count; scalar_t__ retransmit_time; scalar_t__ transaction_start; scalar_t__ transaction_id; int /*<<< orphan*/  receive_message; int /*<<< orphan*/  lease; } ;
typedef  TYPE_1__ sd_dhcp6_client ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP6_STATE_STOPPED ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  event_source_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_dhcp6_lease_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int client_reset(sd_dhcp6_client *client) {
        assert(client);

        client->lease = sd_dhcp6_lease_unref(client->lease);

        client->receive_message =
                sd_event_source_unref(client->receive_message);

        client->transaction_id = 0;
        client->transaction_start = 0;

        client->retransmit_time = 0;
        client->retransmit_count = 0;

        (void) event_source_disable(client->timeout_resend);
        (void) event_source_disable(client->timeout_resend_expire);
        (void) event_source_disable(client->timeout_t1);
        (void) event_source_disable(client->timeout_t2);

        client->state = DHCP6_STATE_STOPPED;

        return 0;
}