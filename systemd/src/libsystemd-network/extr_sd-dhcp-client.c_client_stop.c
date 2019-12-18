#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sd_dhcp_client ;

/* Variables and functions */
 int SD_DHCP_CLIENT_EVENT_STOP ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  client_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  client_notify (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  log_dhcp_client (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  log_dhcp_client_errno (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void client_stop(sd_dhcp_client *client, int error) {
        assert(client);

        if (error < 0)
                log_dhcp_client_errno(client, error, "STOPPED: %m");
        else if (error == SD_DHCP_CLIENT_EVENT_STOP)
                log_dhcp_client(client, "STOPPED");
        else
                log_dhcp_client(client, "STOPPED: Unknown event");

        client_notify(client, error);

        client_initialize(client);
}