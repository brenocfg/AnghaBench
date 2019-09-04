#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int access_denied_notified; scalar_t__ delete_pending; } ;
struct TYPE_17__ {scalar_t__ state; scalar_t__ error; int /*<<< orphan*/  head; scalar_t__ is_clone; int /*<<< orphan*/  repo_id; } ;
struct TYPE_16__ {int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_15__ {int /*<<< orphan*/  head_commit; TYPE_1__* current_task; } ;
struct TYPE_14__ {int /*<<< orphan*/  err_detail; TYPE_6__* repo; } ;
typedef  TYPE_1__ SyncTask ;
typedef  TYPE_2__ SyncInfo ;
typedef  TYPE_3__ SeafileSession ;
typedef  int /*<<< orphan*/  SeafSyncManager ;
typedef  TYPE_4__ HttpTxTask ;

/* Variables and functions */
 scalar_t__ HTTP_TASK_ERR_FILES_LOCKED ; 
 scalar_t__ HTTP_TASK_ERR_FORBIDDEN ; 
 scalar_t__ HTTP_TASK_ERR_NO_PERMISSION_TO_SYNC ; 
 scalar_t__ HTTP_TASK_ERR_NO_WRITE_PERMISSION ; 
 scalar_t__ HTTP_TASK_ERR_REPO_DELETED ; 
 scalar_t__ HTTP_TASK_STATE_CANCELED ; 
 scalar_t__ HTTP_TASK_STATE_ERROR ; 
 scalar_t__ HTTP_TASK_STATE_FINISHED ; 
 int /*<<< orphan*/  SYNC_ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  SYNC_ERROR_FETCH ; 
 int /*<<< orphan*/  SYNC_ERROR_FILES_LOCKED ; 
 int /*<<< orphan*/  SYNC_STATE_CANCELED ; 
 int /*<<< orphan*/  SYNC_STATE_DONE ; 
 int /*<<< orphan*/  g_strdup (int /*<<< orphan*/ ) ; 
 TYPE_2__* get_sync_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_task_error_str (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on_repo_deleted_on_server (TYPE_1__*,TYPE_6__*) ; 
 int /*<<< orphan*/  seaf_repo_manager_del_repo (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  seaf_sync_manager_set_task_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_sync_error_notification (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  transition_sync_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
on_repo_http_fetched (SeafileSession *seaf,
                      HttpTxTask *tx_task,
                      SeafSyncManager *manager)
{
    SyncInfo *info = get_sync_info (manager, tx_task->repo_id);
    SyncTask *task = info->current_task;

    /* Clone tasks are handled by clone manager. */
    if (tx_task->is_clone)
        return;

    if (task->repo->delete_pending) {
        transition_sync_state (task, SYNC_STATE_CANCELED);
        seaf_repo_manager_del_repo (seaf->repo_mgr, task->repo);
        return;
    }

    if (tx_task->state == HTTP_TASK_STATE_FINISHED) {
        memcpy (info->head_commit, tx_task->head, 41);
        transition_sync_state (task, SYNC_STATE_DONE);
    } else if (tx_task->state == HTTP_TASK_STATE_CANCELED) {
        transition_sync_state (task, SYNC_STATE_CANCELED);
    } else if (tx_task->state == HTTP_TASK_STATE_ERROR) {
        if (tx_task->error == HTTP_TASK_ERR_FORBIDDEN ||
            tx_task->error == HTTP_TASK_ERR_NO_WRITE_PERMISSION ||
            tx_task->error == HTTP_TASK_ERR_NO_PERMISSION_TO_SYNC) {
            seaf_sync_manager_set_task_error (task, SYNC_ERROR_ACCESS_DENIED);
            if (!task->repo->access_denied_notified) {
                send_sync_error_notification (task->repo, "sync.access_denied");
                task->repo->access_denied_notified = 1;
            }
        } else if (tx_task->error == HTTP_TASK_ERR_FILES_LOCKED) {
            seaf_sync_manager_set_task_error (task, SYNC_ERROR_FILES_LOCKED);
        } else if (tx_task->error == HTTP_TASK_ERR_REPO_DELETED) {
            on_repo_deleted_on_server (task, task->repo);
        } else
            seaf_sync_manager_set_task_error (task, SYNC_ERROR_FETCH);
        task->err_detail = g_strdup(http_task_error_str(tx_task->error));
    }
}