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
typedef  int /*<<< orphan*/  sd_event_io_handler_t ;
struct TYPE_7__ {int /*<<< orphan*/  receive_message; int /*<<< orphan*/  event_priority; int /*<<< orphan*/  fd; struct TYPE_7__* event; } ;
typedef  TYPE_1__ sd_dhcp_client ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  client_stop (TYPE_1__*,int) ; 
 int sd_event_add_io (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sd_event_source_set_description (int /*<<< orphan*/ ,char*) ; 
 int sd_event_source_set_priority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int client_initialize_io_events(
                sd_dhcp_client *client,
                sd_event_io_handler_t io_callback) {

        int r;

        assert(client);
        assert(client->event);

        r = sd_event_add_io(client->event, &client->receive_message,
                            client->fd, EPOLLIN, io_callback,
                            client);
        if (r < 0)
                goto error;

        r = sd_event_source_set_priority(client->receive_message,
                                         client->event_priority);
        if (r < 0)
                goto error;

        r = sd_event_source_set_description(client->receive_message, "dhcp4-receive-message");
        if (r < 0)
                goto error;

error:
        if (r < 0)
                client_stop(client, r);

        return 0;
}