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
struct TYPE_10__ {scalar_t__ control_pid; scalar_t__ control_command_id; int /*<<< orphan*/  result; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Swap ;
typedef  TYPE_1__ FILE ;
typedef  TYPE_1__ FDSet ;

/* Variables and functions */
 int /*<<< orphan*/  PID_FMT ; 
 TYPE_1__* SWAP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  serialize_item (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serialize_item_format (TYPE_1__*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  swap_exec_command_to_string (scalar_t__) ; 
 int /*<<< orphan*/  swap_result_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_state_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int swap_serialize(Unit *u, FILE *f, FDSet *fds) {
        Swap *s = SWAP(u);

        assert(s);
        assert(f);
        assert(fds);

        (void) serialize_item(f, "state", swap_state_to_string(s->state));
        (void) serialize_item(f, "result", swap_result_to_string(s->result));

        if (s->control_pid > 0)
                (void) serialize_item_format(f, "control-pid", PID_FMT, s->control_pid);

        if (s->control_command_id >= 0)
                (void) serialize_item(f, "control-command", swap_exec_command_to_string(s->control_command_id));

        return 0;
}