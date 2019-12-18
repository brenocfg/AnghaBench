#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wayland_socket_str ;
struct TYPE_3__ {int /*<<< orphan*/  notify; } ;
struct bar_config {char* swaybar_command; char* id; TYPE_1__ client_destroy; int /*<<< orphan*/ * client; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  scalar_t__ pid_t ;
struct TYPE_4__ {int /*<<< orphan*/  wl_display; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  execvp (char* const,char* const*) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  handle_swaybar_client_destroy ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sway_log_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sway_set_cloexec (int,int) ; 
 scalar_t__ waitpid (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_client_add_destroy_listener (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * wl_client_create (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void invoke_swaybar(struct bar_config *bar) {
	int sockets[2];
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) != 0) {
		sway_log_errno(SWAY_ERROR, "socketpair failed");
		return;
	}
	if (!sway_set_cloexec(sockets[0], true) || !sway_set_cloexec(sockets[1], true)) {
		return;
	}

	bar->client = wl_client_create(server.wl_display, sockets[0]);
	if (bar->client == NULL) {
		sway_log_errno(SWAY_ERROR, "wl_client_create failed");
		return;
	}

	bar->client_destroy.notify = handle_swaybar_client_destroy;
	wl_client_add_destroy_listener(bar->client, &bar->client_destroy);

	pid_t pid = fork();
	if (pid < 0) {
		sway_log(SWAY_ERROR, "Failed to create fork for swaybar");
		return;
	} else if (pid == 0) {
		// Remove the SIGUSR1 handler that wlroots adds for xwayland
		sigset_t set;
		sigemptyset(&set);
		sigprocmask(SIG_SETMASK, &set, NULL);

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

			// run custom swaybar
			char *const cmd[] = {
					bar->swaybar_command ? bar->swaybar_command : "swaybar",
					"-b", bar->id, NULL};
			execvp(cmd[0], cmd);
			_exit(EXIT_FAILURE);
		}
		_exit(EXIT_SUCCESS);
	}

	if (close(sockets[1]) != 0) {
		sway_log_errno(SWAY_ERROR, "close failed");
		return;
	}

	if (waitpid(pid, NULL, 0) < 0) {
		sway_log_errno(SWAY_ERROR, "waitpid failed");
		return;
	}

	sway_log(SWAY_DEBUG, "Spawned swaybar %s", bar->id);
	return;
}