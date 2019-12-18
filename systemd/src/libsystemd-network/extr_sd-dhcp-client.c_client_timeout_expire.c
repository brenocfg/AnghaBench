#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_7__ {scalar_t__ state; } ;
typedef  TYPE_1__ sd_dhcp_client ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP_CLIENT_DONT_DESTROY (TYPE_1__*) ; 
 scalar_t__ DHCP_STATE_STOPPED ; 
 int /*<<< orphan*/  SD_DHCP_CLIENT_EVENT_EXPIRED ; 
 int /*<<< orphan*/  client_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  client_notify (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_start (TYPE_1__*) ; 
 int /*<<< orphan*/  log_dhcp_client (TYPE_1__*,char*) ; 

__attribute__((used)) static int client_timeout_expire(sd_event_source *s, uint64_t usec, void *userdata) {
        sd_dhcp_client *client = userdata;
        DHCP_CLIENT_DONT_DESTROY(client);

        log_dhcp_client(client, "EXPIRED");

        client_notify(client, SD_DHCP_CLIENT_EVENT_EXPIRED);

        /* lease was lost, start over if not freed or stopped in callback */
        if (client->state != DHCP_STATE_STOPPED) {
                client_initialize(client);
                client_start(client);
        }

        return 0;
}