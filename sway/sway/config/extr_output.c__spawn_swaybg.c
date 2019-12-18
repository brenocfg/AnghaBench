#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wayland_socket_str ;
typedef  scalar_t__ pid_t ;
struct TYPE_4__ {int /*<<< orphan*/  notify; } ;
struct TYPE_6__ {TYPE_1__ swaybg_client_destroy; int /*<<< orphan*/ * swaybg_client; } ;
struct TYPE_5__ {int /*<<< orphan*/  wl_display; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 scalar_t__ close (int) ; 
 TYPE_3__* config ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  handle_swaybg_client_destroy ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sway_log_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sway_set_cloexec (int,int) ; 
 scalar_t__ waitpid (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_client_add_destroy_listener (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * wl_client_create (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wl_client_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool _spawn_swaybg(char **command) {
	if (config->swaybg_client != NULL) {
		wl_client_destroy(config->swaybg_client);
	}
	int sockets[2];
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) != 0) {
		sway_log_errno(SWAY_ERROR, "socketpair failed");
		return false;
	}
	if (!sway_set_cloexec(sockets[0], true) || !sway_set_cloexec(sockets[1], true)) {
		return false;
	}

	config->swaybg_client = wl_client_create(server.wl_display, sockets[0]);
	if (config->swaybg_client == NULL) {
		sway_log_errno(SWAY_ERROR, "wl_client_create failed");
		return false;
	}

	config->swaybg_client_destroy.notify = handle_swaybg_client_destroy;
	wl_client_add_destroy_listener(config->swaybg_client,
		&config->swaybg_client_destroy);

	pid_t pid = fork();
	if (pid < 0) {
		sway_log_errno(SWAY_ERROR, "fork failed");
		return false;
	} else if (pid == 0) {
		pid = fork();
		if (pid < 0) {
			sway_log_errno(SWAY_ERROR, "fork failed");
			_exit(EXIT_FAILURE);
		} else if (pid == 0) {
			if (!sway_set_cloexec(sockets[1], false)) {
				_exit(EXIT_FAILURE);
			}

			char wayland_socket_str[16];
			snprintf(wayland_socket_str, sizeof(wayland_socket_str),
				"%d", sockets[1]);
			setenv("WAYLAND_SOCKET", wayland_socket_str, true);

			execvp(command[0], command);
			sway_log_errno(SWAY_ERROR, "execvp failed");
			_exit(EXIT_FAILURE);
		}
		_exit(EXIT_SUCCESS);
	}

	if (close(sockets[1]) != 0) {
		sway_log_errno(SWAY_ERROR, "close failed");
		return false;
	}
	if (waitpid(pid, NULL, 0) < 0) {
		sway_log_errno(SWAY_ERROR, "waitpid failed");
		return false;
	}

	return true;
}