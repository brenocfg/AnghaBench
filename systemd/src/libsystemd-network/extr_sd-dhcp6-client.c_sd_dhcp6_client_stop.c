#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ sd_dhcp6_client ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SD_DHCP6_CLIENT_EVENT_STOP ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_stop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 

int sd_dhcp6_client_stop(sd_dhcp6_client *client) {
        assert_return(client, -EINVAL);

        client_stop(client, SD_DHCP6_CLIENT_EVENT_STOP);

        client->fd = safe_close(client->fd);

        return 0;
}