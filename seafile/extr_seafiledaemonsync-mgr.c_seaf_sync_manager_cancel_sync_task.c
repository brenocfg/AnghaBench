#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  http_tx_mgr; int /*<<< orphan*/  started; } ;
struct TYPE_10__ {int /*<<< orphan*/  sync_infos; } ;
struct TYPE_9__ {TYPE_1__* current_task; scalar_t__ sync_perm_err_cnt; int /*<<< orphan*/  in_error; scalar_t__ err_cnt; int /*<<< orphan*/  in_sync; } ;
struct TYPE_8__ {scalar_t__ state; } ;
typedef  TYPE_1__ SyncTask ;
typedef  TYPE_2__ SyncInfo ;
typedef  TYPE_3__ SeafSyncManager ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HTTP_TASK_TYPE_DOWNLOAD ; 
 int /*<<< orphan*/  HTTP_TASK_TYPE_UPLOAD ; 
#define  SYNC_STATE_CANCEL_PENDING 133 
#define  SYNC_STATE_COMMIT 132 
 scalar_t__ SYNC_STATE_ERROR ; 
#define  SYNC_STATE_FETCH 131 
#define  SYNC_STATE_INIT 130 
#define  SYNC_STATE_MERGE 129 
#define  SYNC_STATE_UPLOAD 128 
 TYPE_2__* g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  g_return_if_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_return_if_reached () ; 
 int /*<<< orphan*/  http_tx_manager_cancel_task (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 TYPE_6__* seaf ; 
 int /*<<< orphan*/  seaf_message (char*) ; 
 int /*<<< orphan*/  transition_sync_state (TYPE_1__*,int) ; 

void
seaf_sync_manager_cancel_sync_task (SeafSyncManager *mgr,
                                    const char *repo_id)
{
    SyncInfo *info;
    SyncTask *task;

    if (!seaf->started) {
        seaf_message ("sync manager is not started, skip cancel request.\n");
        return;
    }

    /* Cancel running task. */
    info = g_hash_table_lookup (mgr->sync_infos, repo_id);

    if (!info)
        return;
    else if (!info->in_sync) {
        if (info->current_task->state == SYNC_STATE_ERROR) {
            info->err_cnt = 0;
            info->in_error = FALSE;
            info->sync_perm_err_cnt = 0;
        }
        return;
    }

    g_return_if_fail (info->current_task != NULL);
    task = info->current_task;

    switch (task->state) {
    case SYNC_STATE_FETCH:
        http_tx_manager_cancel_task (seaf->http_tx_mgr,
                                     repo_id,
                                     HTTP_TASK_TYPE_DOWNLOAD);
        transition_sync_state (task, SYNC_STATE_CANCEL_PENDING);
        break;
    case SYNC_STATE_UPLOAD:
        http_tx_manager_cancel_task (seaf->http_tx_mgr,
                                     repo_id,
                                     HTTP_TASK_TYPE_UPLOAD);
        transition_sync_state (task, SYNC_STATE_CANCEL_PENDING);
        break;
    case SYNC_STATE_COMMIT:
    case SYNC_STATE_INIT:
    case SYNC_STATE_MERGE:
        transition_sync_state (task, SYNC_STATE_CANCEL_PENDING);
        break;
    case SYNC_STATE_CANCEL_PENDING:
        break;
    default:
        g_return_if_reached ();
    }
}