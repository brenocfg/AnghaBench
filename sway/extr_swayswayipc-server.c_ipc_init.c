#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sway_server {int /*<<< orphan*/  wl_event_loop; int /*<<< orphan*/  wl_display; } ;
struct sockaddr {int dummy; } ;
struct TYPE_6__ {scalar_t__* sun_path; } ;
struct TYPE_5__ {int /*<<< orphan*/  notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  WL_EVENT_READABLE ; 
 int access (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  create_list () ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  handle_display_destroy ; 
 int /*<<< orphan*/  ipc_client_list ; 
 TYPE_1__ ipc_display_destroy ; 
 int /*<<< orphan*/  ipc_event_source ; 
 int /*<<< orphan*/  ipc_handle_connection ; 
 TYPE_2__* ipc_sockaddr ; 
 int ipc_socket ; 
 TYPE_2__* ipc_user_sockaddr () ; 
 int listen (int,int) ; 
 int /*<<< orphan*/  setenv (char*,scalar_t__*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sway_abort (char*) ; 
 int /*<<< orphan*/  unlink (scalar_t__*) ; 
 int /*<<< orphan*/  wl_display_add_destroy_listener (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  wl_event_loop_add_fd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sway_server*) ; 

void ipc_init(struct sway_server *server) {
	ipc_socket = socket(AF_UNIX, SOCK_STREAM, 0);
	if (ipc_socket == -1) {
		sway_abort("Unable to create IPC socket");
	}
	if (fcntl(ipc_socket, F_SETFD, FD_CLOEXEC) == -1) {
		sway_abort("Unable to set CLOEXEC on IPC socket");
	}
	if (fcntl(ipc_socket, F_SETFL, O_NONBLOCK) == -1) {
		sway_abort("Unable to set NONBLOCK on IPC socket");
	}

	ipc_sockaddr = ipc_user_sockaddr();

	// We want to use socket name set by user, not existing socket from another sway instance.
	if (getenv("SWAYSOCK") != NULL && access(getenv("SWAYSOCK"), F_OK) == -1) {
		strncpy(ipc_sockaddr->sun_path, getenv("SWAYSOCK"), sizeof(ipc_sockaddr->sun_path) - 1);
		ipc_sockaddr->sun_path[sizeof(ipc_sockaddr->sun_path) - 1] = 0;
	}

	unlink(ipc_sockaddr->sun_path);
	if (bind(ipc_socket, (struct sockaddr *)ipc_sockaddr, sizeof(*ipc_sockaddr)) == -1) {
		sway_abort("Unable to bind IPC socket");
	}

	if (listen(ipc_socket, 3) == -1) {
		sway_abort("Unable to listen on IPC socket");
	}

	// Set i3 IPC socket path so that i3-msg works out of the box
	setenv("I3SOCK", ipc_sockaddr->sun_path, 1);
	setenv("SWAYSOCK", ipc_sockaddr->sun_path, 1);

	ipc_client_list = create_list();

	ipc_display_destroy.notify = handle_display_destroy;
	wl_display_add_destroy_listener(server->wl_display, &ipc_display_destroy);

	ipc_event_source = wl_event_loop_add_fd(server->wl_event_loop, ipc_socket,
			WL_EVENT_READABLE, ipc_handle_connection, server);
}