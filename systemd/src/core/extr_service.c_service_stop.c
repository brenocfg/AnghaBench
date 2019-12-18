#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_8__ {int forbid_restart; scalar_t__ state; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 TYPE_1__* IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 TYPE_1__* SERVICE (int /*<<< orphan*/ *) ; 
 scalar_t__ SERVICE_AUTO_RESTART ; 
 scalar_t__ SERVICE_CLEANING ; 
 int /*<<< orphan*/  SERVICE_CONDITION ; 
 int /*<<< orphan*/  SERVICE_DEAD ; 
 int /*<<< orphan*/  SERVICE_EXITED ; 
 int /*<<< orphan*/  SERVICE_FINAL_SIGKILL ; 
 int /*<<< orphan*/  SERVICE_FINAL_SIGTERM ; 
 int /*<<< orphan*/  SERVICE_RELOAD ; 
 int /*<<< orphan*/  SERVICE_RUNNING ; 
 int /*<<< orphan*/  SERVICE_START ; 
 int /*<<< orphan*/  SERVICE_START_POST ; 
 int /*<<< orphan*/  SERVICE_START_PRE ; 
 int /*<<< orphan*/  SERVICE_STOP ; 
 int /*<<< orphan*/  SERVICE_STOP_POST ; 
 int /*<<< orphan*/  SERVICE_STOP_SIGKILL ; 
 int /*<<< orphan*/  SERVICE_STOP_SIGTERM ; 
 int /*<<< orphan*/  SERVICE_STOP_WATCHDOG ; 
 int /*<<< orphan*/  SERVICE_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  service_enter_signal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_enter_stop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int service_stop(Unit *u) {
        Service *s = SERVICE(u);

        assert(s);

        /* Don't create restart jobs from manual stops. */
        s->forbid_restart = true;

        /* Already on it */
        if (IN_SET(s->state,
                   SERVICE_STOP, SERVICE_STOP_SIGTERM, SERVICE_STOP_SIGKILL, SERVICE_STOP_POST,
                   SERVICE_FINAL_SIGTERM, SERVICE_FINAL_SIGKILL))
                return 0;

        /* A restart will be scheduled or is in progress. */
        if (s->state == SERVICE_AUTO_RESTART) {
                service_set_state(s, SERVICE_DEAD);
                return 0;
        }

        /* If there's already something running we go directly into
         * kill mode. */
        if (IN_SET(s->state, SERVICE_CONDITION, SERVICE_START_PRE, SERVICE_START, SERVICE_START_POST, SERVICE_RELOAD, SERVICE_STOP_WATCHDOG)) {
                service_enter_signal(s, SERVICE_STOP_SIGTERM, SERVICE_SUCCESS);
                return 0;
        }

        /* If we are currently cleaning, then abort it, brutally. */
        if (s->state == SERVICE_CLEANING) {
                service_enter_signal(s, SERVICE_FINAL_SIGKILL, SERVICE_SUCCESS);
                return 0;
        }

        assert(IN_SET(s->state, SERVICE_RUNNING, SERVICE_EXITED));

        service_enter_stop(s, SERVICE_SUCCESS);
        return 1;
}