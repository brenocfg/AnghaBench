#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_10__ {int state; int /*<<< orphan*/  pid_file_pathspec; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 TYPE_1__* SERVICE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SERVICE_FAILURE_PROTOCOL ; 
#define  SERVICE_FINAL_SIGKILL 136 
#define  SERVICE_FINAL_SIGTERM 135 
 int /*<<< orphan*/  SERVICE_NOTIFY ; 
#define  SERVICE_RUNNING 134 
#define  SERVICE_START 133 
#define  SERVICE_START_POST 132 
#define  SERVICE_STOP_POST 131 
#define  SERVICE_STOP_SIGKILL 130 
#define  SERVICE_STOP_SIGTERM 129 
#define  SERVICE_STOP_WATCHDOG 128 
 int /*<<< orphan*/  SERVICE_SUCCESS ; 
 int /*<<< orphan*/  _fallthrough_ ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  control_pid_good (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  log_unit_warning (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  main_pid_good (TYPE_1__*) ; 
 int /*<<< orphan*/  service_enter_dead (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  service_enter_running (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_enter_stop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_enter_stop_post (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_unwatch_pid_file (TYPE_1__*) ; 

__attribute__((used)) static void service_notify_cgroup_empty_event(Unit *u) {
        Service *s = SERVICE(u);

        assert(u);

        log_unit_debug(u, "Control group is empty.");

        switch (s->state) {

                /* Waiting for SIGCHLD is usually more interesting,
                 * because it includes return codes/signals. Which is
                 * why we ignore the cgroup events for most cases,
                 * except when we don't know pid which to expect the
                 * SIGCHLD for. */

        case SERVICE_START:
                if (s->type == SERVICE_NOTIFY &&
                    main_pid_good(s) == 0 &&
                    control_pid_good(s) == 0) {
                        /* No chance of getting a ready notification anymore */
                        service_enter_stop_post(s, SERVICE_FAILURE_PROTOCOL);
                        break;
                }

                _fallthrough_;
        case SERVICE_START_POST:
                if (s->pid_file_pathspec &&
                    main_pid_good(s) == 0 &&
                    control_pid_good(s) == 0) {

                        /* Give up hoping for the daemon to write its PID file */
                        log_unit_warning(u, "Daemon never wrote its PID file. Failing.");

                        service_unwatch_pid_file(s);
                        if (s->state == SERVICE_START)
                                service_enter_stop_post(s, SERVICE_FAILURE_PROTOCOL);
                        else
                                service_enter_stop(s, SERVICE_FAILURE_PROTOCOL);
                }
                break;

        case SERVICE_RUNNING:
                /* service_enter_running() will figure out what to do */
                service_enter_running(s, SERVICE_SUCCESS);
                break;

        case SERVICE_STOP_WATCHDOG:
        case SERVICE_STOP_SIGTERM:
        case SERVICE_STOP_SIGKILL:

                if (main_pid_good(s) <= 0 && control_pid_good(s) <= 0)
                        service_enter_stop_post(s, SERVICE_SUCCESS);

                break;

        case SERVICE_STOP_POST:
        case SERVICE_FINAL_SIGTERM:
        case SERVICE_FINAL_SIGKILL:
                if (main_pid_good(s) <= 0 && control_pid_good(s) <= 0)
                        service_enter_dead(s, SERVICE_SUCCESS, true);

                break;

        default:
                ;
        }
}