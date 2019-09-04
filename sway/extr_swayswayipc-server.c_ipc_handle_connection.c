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
typedef  scalar_t__ uint32_t ;
struct sway_server {int /*<<< orphan*/  wl_event_loop; } ;
struct ipc_client {int fd; int write_buffer_size; void* write_buffer; scalar_t__ write_buffer_len; int /*<<< orphan*/ * writable_event_source; int /*<<< orphan*/  event_source; scalar_t__ subscribed_events; scalar_t__ pending_length; struct sway_server* server; } ;

/* Variables and functions */
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 scalar_t__ WL_EVENT_READABLE ; 
 int accept (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ipc_client_handle_readable ; 
 int /*<<< orphan*/  ipc_client_list ; 
 int /*<<< orphan*/  ipc_socket ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ ,struct ipc_client*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sway_log_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl_event_loop_add_fd (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,struct ipc_client*) ; 

int ipc_handle_connection(int fd, uint32_t mask, void *data) {
	(void) fd;
	struct sway_server *server = data;
	sway_log(SWAY_DEBUG, "Event on IPC listening socket");
	assert(mask == WL_EVENT_READABLE);

	int client_fd = accept(ipc_socket, NULL, NULL);
	if (client_fd == -1) {
		sway_log_errno(SWAY_ERROR, "Unable to accept IPC client connection");
		return 0;
	}

	int flags;
	if ((flags = fcntl(client_fd, F_GETFD)) == -1
			|| fcntl(client_fd, F_SETFD, flags|FD_CLOEXEC) == -1) {
		sway_log_errno(SWAY_ERROR, "Unable to set CLOEXEC on IPC client socket");
		close(client_fd);
		return 0;
	}
	if ((flags = fcntl(client_fd, F_GETFL)) == -1
			|| fcntl(client_fd, F_SETFL, flags|O_NONBLOCK) == -1) {
		sway_log_errno(SWAY_ERROR, "Unable to set NONBLOCK on IPC client socket");
		close(client_fd);
		return 0;
	}

	struct ipc_client *client = malloc(sizeof(struct ipc_client));
	if (!client) {
		sway_log(SWAY_ERROR, "Unable to allocate ipc client");
		close(client_fd);
		return 0;
	}
	client->server = server;
	client->pending_length = 0;
	client->fd = client_fd;
	client->subscribed_events = 0;
	client->event_source = wl_event_loop_add_fd(server->wl_event_loop,
			client_fd, WL_EVENT_READABLE, ipc_client_handle_readable, client);
	client->writable_event_source = NULL;

	client->write_buffer_size = 128;
	client->write_buffer_len = 0;
	client->write_buffer = malloc(client->write_buffer_size);
	if (!client->write_buffer) {
		sway_log(SWAY_ERROR, "Unable to allocate ipc client write buffer");
		close(client_fd);
		return 0;
	}

	sway_log(SWAY_DEBUG, "New client: fd %d", client_fd);
	list_add(ipc_client_list, client);
	return 0;
}