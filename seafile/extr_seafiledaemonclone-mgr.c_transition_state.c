#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t state; int /*<<< orphan*/  repo_id; int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ CloneTask ;

/* Variables and functions */
 int CLONE_STATE_CANCELED ; 
 int CLONE_STATE_DONE ; 
 int /*<<< orphan*/  remove_task_from_db (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_message (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * state_str ; 

__attribute__((used)) static void
transition_state (CloneTask *task, int new_state)
{
    seaf_message ("Transition clone state for %.8s from [%s] to [%s].\n",
                  task->repo_id,
                  state_str[task->state], state_str[new_state]);

    if (new_state == CLONE_STATE_DONE ||
        new_state == CLONE_STATE_CANCELED) {
        /* Remove from db but leave in memory. */
        remove_task_from_db (task->manager, task->repo_id);
    }

    task->state = new_state;
}