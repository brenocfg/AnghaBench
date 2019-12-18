#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_5__ {int /*<<< orphan*/  timer_event_source; int /*<<< orphan*/  dynamic_creds; int /*<<< orphan*/ * control_command; int /*<<< orphan*/  exec_command; int /*<<< orphan*/  exec_runtime; int /*<<< orphan*/  parameters_fragment; int /*<<< orphan*/  parameters_proc_self_mountinfo; int /*<<< orphan*/  where; } ;
typedef  TYPE_1__ Mount ;

/* Variables and functions */
 TYPE_1__* MOUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _MOUNT_EXEC_COMMAND_MAX ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dynamic_creds_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_command_done_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_runtime_unref (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_parameters_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mount_unwatch_control_pid (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mount_done(Unit *u) {
        Mount *m = MOUNT(u);

        assert(m);

        m->where = mfree(m->where);

        mount_parameters_done(&m->parameters_proc_self_mountinfo);
        mount_parameters_done(&m->parameters_fragment);

        m->exec_runtime = exec_runtime_unref(m->exec_runtime, false);
        exec_command_done_array(m->exec_command, _MOUNT_EXEC_COMMAND_MAX);
        m->control_command = NULL;

        dynamic_creds_unref(&m->dynamic_creds);

        mount_unwatch_control_pid(m);

        m->timer_event_source = sd_event_source_unref(m->timer_event_source);
}