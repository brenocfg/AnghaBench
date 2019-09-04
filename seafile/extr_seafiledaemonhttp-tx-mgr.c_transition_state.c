#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_5__ {int state; int runtime_state; scalar_t__ type; int /*<<< orphan*/  repo_id; } ;
typedef  TYPE_1__ HttpTxTask ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_SHA1 ; 
 int HTTP_TASK_RT_STATE_FINISHED ; 
 int HTTP_TASK_STATE_FINISHED ; 
 scalar_t__ HTTP_TASK_TYPE_DOWNLOAD ; 
 int /*<<< orphan*/  REPO_PROP_DOWNLOAD_HEAD ; 
 int /*<<< orphan*/  emit_transfer_done_signal (TYPE_1__*) ; 
 int /*<<< orphan*/  http_task_rt_state_to_str (int) ; 
 int /*<<< orphan*/  http_task_state_to_str (int) ; 
 TYPE_3__* seaf ; 
 int /*<<< orphan*/  seaf_message (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_repo_manager_set_repo_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
transition_state (HttpTxTask *task, int state, int rt_state)
{
    seaf_message ("Transfer repo '%.8s': ('%s', '%s') --> ('%s', '%s')\n",
                  task->repo_id,
                  http_task_state_to_str(task->state),
                  http_task_rt_state_to_str(task->runtime_state),
                  http_task_state_to_str(state),
                  http_task_rt_state_to_str(rt_state));

    if (state != task->state)
        task->state = state;
    task->runtime_state = rt_state;

    if (rt_state == HTTP_TASK_RT_STATE_FINISHED) {
        /* Clear download head info. */
        if (task->type == HTTP_TASK_TYPE_DOWNLOAD &&
            state == HTTP_TASK_STATE_FINISHED)
            seaf_repo_manager_set_repo_property (seaf->repo_mgr,
                                                 task->repo_id,
                                                 REPO_PROP_DOWNLOAD_HEAD,
                                                 EMPTY_SHA1);

        emit_transfer_done_signal (task);
    }
}