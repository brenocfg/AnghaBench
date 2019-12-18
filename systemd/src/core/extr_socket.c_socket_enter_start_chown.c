#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  control_pid; int /*<<< orphan*/ * control_command; int /*<<< orphan*/  control_command_id; int /*<<< orphan*/  group; int /*<<< orphan*/  user; } ;
typedef  TYPE_1__ Socket ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET_EXEC_START_CHOWN ; 
 int /*<<< orphan*/  SOCKET_FAILURE_RESOURCES ; 
 int /*<<< orphan*/  SOCKET_START_CHOWN ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  isempty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_unit_warning_errno (int /*<<< orphan*/ ,int,char*) ; 
 int socket_chown (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_enter_start_post (TYPE_1__*) ; 
 int /*<<< orphan*/  socket_enter_stop_pre (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int socket_open_fds (TYPE_1__*) ; 
 int /*<<< orphan*/  socket_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unwatch_control_pid (TYPE_1__*) ; 

__attribute__((used)) static void socket_enter_start_chown(Socket *s) {
        int r;

        assert(s);

        r = socket_open_fds(s);
        if (r < 0) {
                log_unit_warning_errno(UNIT(s), r, "Failed to listen on sockets: %m");
                goto fail;
        }

        if (!isempty(s->user) || !isempty(s->group)) {

                socket_unwatch_control_pid(s);
                s->control_command_id = SOCKET_EXEC_START_CHOWN;
                s->control_command = NULL;

                r = socket_chown(s, &s->control_pid);
                if (r < 0) {
                        log_unit_warning_errno(UNIT(s), r, "Failed to fork 'start-chown' task: %m");
                        goto fail;
                }

                socket_set_state(s, SOCKET_START_CHOWN);
        } else
                socket_enter_start_post(s);

        return;

fail:
        socket_enter_stop_pre(s, SOCKET_FAILURE_RESOURCES);
}