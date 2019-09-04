#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t state; int error; TYPE_2__* mgr; TYPE_1__* info; TYPE_3__* repo; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  n_running_tasks; } ;
struct TYPE_7__ {int /*<<< orphan*/  in_sync; } ;
typedef  TYPE_4__ SyncTask ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SYNC_ERROR_NUM ; 
 size_t SYNC_STATE_ERROR ; 
 int /*<<< orphan*/  g_return_if_fail (int) ; 
 int /*<<< orphan*/  seaf_message (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sync_error_str ; 
 int /*<<< orphan*/ * sync_state_str ; 
 int /*<<< orphan*/  update_sync_info_error_state (TYPE_4__*,size_t) ; 

void
seaf_sync_manager_set_task_error (SyncTask *task, int error)
{
    g_return_if_fail (error >= 0 && error < SYNC_ERROR_NUM);

    if (task->state != SYNC_STATE_ERROR) {
        seaf_message ("Repo '%s' sync state transition from %s to '%s': '%s'.\n",
                      task->repo->name,
                      sync_state_str[task->state],
                      sync_state_str[SYNC_STATE_ERROR],
                      sync_error_str[error]);
        task->state = SYNC_STATE_ERROR;
        task->error = error;
        task->info->in_sync = FALSE;
        --(task->mgr->n_running_tasks);
        update_sync_info_error_state (task, SYNC_STATE_ERROR);

#ifdef WIN32
        seaf_sync_manager_add_refresh_path (seaf->sync_mgr, task->repo->worktree);
#endif

    }
}