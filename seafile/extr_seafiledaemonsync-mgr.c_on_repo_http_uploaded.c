#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int access_denied_notified; int quota_full_notified; TYPE_1__* head; int /*<<< orphan*/  id; scalar_t__ delete_pending; } ;
struct TYPE_20__ {scalar_t__ state; scalar_t__ error; int /*<<< orphan*/  head; int /*<<< orphan*/  repo_id; } ;
struct TYPE_19__ {int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_18__ {int /*<<< orphan*/  head_commit; scalar_t__ in_sync; TYPE_2__* current_task; } ;
struct TYPE_17__ {int /*<<< orphan*/  err_detail; TYPE_7__* repo; int /*<<< orphan*/  uploaded; } ;
struct TYPE_16__ {int /*<<< orphan*/  commit_id; } ;
typedef  TYPE_2__ SyncTask ;
typedef  TYPE_3__ SyncInfo ;
typedef  TYPE_4__ SeafileSession ;
typedef  int /*<<< orphan*/  SeafSyncManager ;
typedef  TYPE_5__ HttpTxTask ;

/* Variables and functions */
 scalar_t__ HTTP_TASK_ERR_FORBIDDEN ; 
 scalar_t__ HTTP_TASK_ERR_NO_PERMISSION_TO_SYNC ; 
 scalar_t__ HTTP_TASK_ERR_NO_QUOTA ; 
 scalar_t__ HTTP_TASK_ERR_NO_WRITE_PERMISSION ; 
 scalar_t__ HTTP_TASK_ERR_REPO_DELETED ; 
 scalar_t__ HTTP_TASK_STATE_CANCELED ; 
 scalar_t__ HTTP_TASK_STATE_ERROR ; 
 scalar_t__ HTTP_TASK_STATE_FINISHED ; 
 int /*<<< orphan*/  REPO_LOCAL_HEAD ; 
 int /*<<< orphan*/  SYNC_ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  SYNC_ERROR_QUOTA_FULL ; 
 int /*<<< orphan*/  SYNC_ERROR_UPLOAD ; 
 int /*<<< orphan*/  SYNC_STATE_CANCELED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  check_head_commit_http (TYPE_2__*) ; 
 int /*<<< orphan*/  g_return_if_fail (int) ; 
 int /*<<< orphan*/  g_strdup (int /*<<< orphan*/ ) ; 
 TYPE_3__* get_sync_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_task_error_str (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on_repo_deleted_on_server (TYPE_2__*,TYPE_7__*) ; 
 int /*<<< orphan*/  seaf_repo_manager_del_repo (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  seaf_repo_manager_set_repo_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_sync_manager_set_task_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_sync_error_notification (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  transition_sync_state (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
on_repo_http_uploaded (SeafileSession *seaf,
                       HttpTxTask *tx_task,
                       SeafSyncManager *manager)
{
    SyncInfo *info = get_sync_info (manager, tx_task->repo_id);
    SyncTask *task = info->current_task;

    g_return_if_fail (task != NULL && info->in_sync);

    if (task->repo->delete_pending) {
        transition_sync_state (task, SYNC_STATE_CANCELED);
        seaf_repo_manager_del_repo (seaf->repo_mgr, task->repo);
        return;
    }

    if (tx_task->state == HTTP_TASK_STATE_FINISHED) {
        memcpy (info->head_commit, tx_task->head, 41);

        /* Save current head commit id for GC. */
        seaf_repo_manager_set_repo_property (seaf->repo_mgr,
                                             task->repo->id,
                                             REPO_LOCAL_HEAD,
                                             task->repo->head->commit_id);
        task->uploaded = TRUE;
        check_head_commit_http (task);
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
        } else if (tx_task->error == HTTP_TASK_ERR_NO_QUOTA) {
            seaf_sync_manager_set_task_error (task, SYNC_ERROR_QUOTA_FULL);
            /* Only notify "quota full" once. */
            if (!task->repo->quota_full_notified) {
                send_sync_error_notification (task->repo, "sync.quota_full");
                task->repo->quota_full_notified = 1;
            }
        } else if (tx_task->error == HTTP_TASK_ERR_REPO_DELETED) {
            on_repo_deleted_on_server (task, task->repo);
        } else
            seaf_sync_manager_set_task_error (task, SYNC_ERROR_UPLOAD);
        task->err_detail = g_strdup(http_task_error_str(tx_task->error));
    }
}