#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ipc_client {int /*<<< orphan*/  fd; struct ipc_client* write_buffer; scalar_t__ writable_event_source; scalar_t__ event_source; } ;
struct TYPE_3__ {int length; struct ipc_client** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  SWAY_INFO ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ipc_client*) ; 
 TYPE_1__* ipc_client_list ; 
 int /*<<< orphan*/  list_del (TYPE_1__*,int) ; 
 int /*<<< orphan*/  shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_assert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_event_source_remove (scalar_t__) ; 

void ipc_client_disconnect(struct ipc_client *client) {
	if (!sway_assert(client != NULL, "client != NULL")) {
		return;
	}

	shutdown(client->fd, SHUT_RDWR);

	sway_log(SWAY_INFO, "IPC Client %d disconnected", client->fd);
	wl_event_source_remove(client->event_source);
	if (client->writable_event_source) {
		wl_event_source_remove(client->writable_event_source);
	}
	int i = 0;
	while (i < ipc_client_list->length && ipc_client_list->items[i] != client) {
		i++;
	}
	list_del(ipc_client_list, i);
	free(client->write_buffer);
	close(client->fd);
	free(client);
}