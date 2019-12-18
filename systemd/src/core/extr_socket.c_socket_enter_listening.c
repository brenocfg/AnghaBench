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
typedef  int /*<<< orphan*/  Socket ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET_FAILURE_RESOURCES ; 
 int /*<<< orphan*/  SOCKET_LISTENING ; 
 int /*<<< orphan*/  UNIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_unit_warning_errno (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  socket_enter_stop_pre (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int socket_watch_fds (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void socket_enter_listening(Socket *s) {
        int r;
        assert(s);

        r = socket_watch_fds(s);
        if (r < 0) {
                log_unit_warning_errno(UNIT(s), r, "Failed to watch sockets: %m");
                goto fail;
        }

        socket_set_state(s, SOCKET_LISTENING);
        return;

fail:
        socket_enter_stop_pre(s, SOCKET_FAILURE_RESOURCES);
}