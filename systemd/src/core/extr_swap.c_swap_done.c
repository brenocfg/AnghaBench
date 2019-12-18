#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_8__ {void* options; void* what; } ;
struct TYPE_9__ {int /*<<< orphan*/  timer_event_source; int /*<<< orphan*/  dynamic_creds; int /*<<< orphan*/ * control_command; int /*<<< orphan*/  exec_command; int /*<<< orphan*/  exec_runtime; TYPE_1__ parameters_fragment; void* what; } ;
typedef  TYPE_2__ Swap ;

/* Variables and functions */
 TYPE_2__* SWAP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _SWAP_EXEC_COMMAND_MAX ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  dynamic_creds_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_command_done_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_runtime_unref (int /*<<< orphan*/ ,int) ; 
 void* mfree (void*) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_set_devnode (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_unset_proc_swaps (TYPE_2__*) ; 
 int /*<<< orphan*/  swap_unwatch_control_pid (TYPE_2__*) ; 

__attribute__((used)) static void swap_done(Unit *u) {
        Swap *s = SWAP(u);

        assert(s);

        swap_unset_proc_swaps(s);
        swap_set_devnode(s, NULL);

        s->what = mfree(s->what);
        s->parameters_fragment.what = mfree(s->parameters_fragment.what);
        s->parameters_fragment.options = mfree(s->parameters_fragment.options);

        s->exec_runtime = exec_runtime_unref(s->exec_runtime, false);
        exec_command_done_array(s->exec_command, _SWAP_EXEC_COMMAND_MAX);
        s->control_command = NULL;

        dynamic_creds_unref(&s->dynamic_creds);

        swap_unwatch_control_pid(s);

        s->timer_event_source = sd_event_source_unref(s->timer_event_source);
}