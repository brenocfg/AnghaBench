#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_4__ {int /*<<< orphan*/  state; int /*<<< orphan*/  exec_context; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* SERVICE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SERVICE_CONDITION ; 
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
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  exec_context_may_touch_console (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool service_needs_console(Unit *u) {
        Service *s = SERVICE(u);

        assert(s);

        /* We provide our own implementation of this here, instead of relying of the generic implementation
         * unit_needs_console() provides, since we want to return false if we are in SERVICE_EXITED state. */

        if (!exec_context_may_touch_console(&s->exec_context))
                return false;

        return IN_SET(s->state,
                      SERVICE_CONDITION,
                      SERVICE_START_PRE,
                      SERVICE_START,
                      SERVICE_START_POST,
                      SERVICE_RUNNING,
                      SERVICE_RELOAD,
                      SERVICE_STOP,
                      SERVICE_STOP_WATCHDOG,
                      SERVICE_STOP_SIGTERM,
                      SERVICE_STOP_SIGKILL,
                      SERVICE_STOP_POST,
                      SERVICE_FINAL_SIGTERM,
                      SERVICE_FINAL_SIGKILL);
}