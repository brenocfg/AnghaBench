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
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ sd_dhcp_client ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP_CLIENT_DONT_DESTROY (TYPE_1__*) ; 
 int /*<<< orphan*/  DHCP_STATE_STOPPED ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SD_DHCP_CLIENT_EVENT_STOP ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_stop (TYPE_1__*,int /*<<< orphan*/ ) ; 

int sd_dhcp_client_stop(sd_dhcp_client *client) {
        DHCP_CLIENT_DONT_DESTROY(client);

        assert_return(client, -EINVAL);

        client_stop(client, SD_DHCP_CLIENT_EVENT_STOP);
        client->state = DHCP_STATE_STOPPED;

        return 0;
}