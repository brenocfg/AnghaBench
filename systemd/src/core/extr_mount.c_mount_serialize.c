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
struct TYPE_10__ {scalar_t__ n_retry_umount; scalar_t__ control_pid; scalar_t__ control_command_id; int /*<<< orphan*/  reload_result; int /*<<< orphan*/  result; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Mount ;
typedef  TYPE_1__ FILE ;
typedef  TYPE_1__ FDSet ;

/* Variables and functions */
 TYPE_1__* MOUNT (int /*<<< orphan*/ *) ; 
 char* PID_FMT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  mount_exec_command_to_string (scalar_t__) ; 
 int /*<<< orphan*/  mount_result_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_state_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serialize_item (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serialize_item_format (TYPE_1__*,char*,char*,scalar_t__) ; 

__attribute__((used)) static int mount_serialize(Unit *u, FILE *f, FDSet *fds) {
        Mount *m = MOUNT(u);

        assert(m);
        assert(f);
        assert(fds);

        (void) serialize_item(f, "state", mount_state_to_string(m->state));
        (void) serialize_item(f, "result", mount_result_to_string(m->result));
        (void) serialize_item(f, "reload-result", mount_result_to_string(m->reload_result));
        (void) serialize_item_format(f, "n-retry-umount", "%u", m->n_retry_umount);

        if (m->control_pid > 0)
                (void) serialize_item_format(f, "control-pid", PID_FMT, m->control_pid);

        if (m->control_command_id >= 0)
                (void) serialize_item(f, "control-command", mount_exec_command_to_string(m->control_command_id));

        return 0;
}