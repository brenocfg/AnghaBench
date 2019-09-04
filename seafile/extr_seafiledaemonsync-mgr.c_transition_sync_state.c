#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {scalar_t__ uploaded_bytes; scalar_t__ total_bytes; void* end_multipart_upload; void* multipart_upload; void* in_sync; } ;
struct TYPE_10__ {int state; TYPE_1__* mgr; TYPE_6__* repo; scalar_t__ uploaded; TYPE_3__* info; } ;
struct TYPE_9__ {int /*<<< orphan*/  n_running_tasks; } ;
typedef  TYPE_2__ SyncTask ;
typedef  TYPE_3__ SyncInfo ;

/* Variables and functions */
 void* FALSE ; 
 int SYNC_STATE_CANCELED ; 
 int SYNC_STATE_DONE ; 
 int SYNC_STATE_ERROR ; 
 int SYNC_STATE_FETCH ; 
 int SYNC_STATE_INIT ; 
 int SYNC_STATE_NUM ; 
 int /*<<< orphan*/  commit_repo (TYPE_2__*) ; 
 int /*<<< orphan*/  g_return_if_fail (int) ; 
 scalar_t__ need_notify_sync (TYPE_6__*) ; 
 int /*<<< orphan*/  notify_sync (TYPE_6__*,int) ; 
 int /*<<< orphan*/  seaf_message (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sync_state_str ; 
 int /*<<< orphan*/  update_sync_info_error_state (TYPE_2__*,int) ; 

__attribute__((used)) static inline void
transition_sync_state (SyncTask *task, int new_state)
{
    g_return_if_fail (new_state >= 0 && new_state < SYNC_STATE_NUM);

    SyncInfo *info = task->info;

    if (task->state != new_state) {
        if (((task->state == SYNC_STATE_INIT && task->uploaded) ||
             task->state == SYNC_STATE_FETCH) &&
            new_state == SYNC_STATE_DONE &&
            need_notify_sync(task->repo))
            notify_sync (task->repo, (info->multipart_upload && !info->end_multipart_upload));

        /* If we're in the process of uploading large set of files, they'll be splitted
         * into multiple batches for upload. We want to immediately start the next batch
         * after previous one is done.
         */
        if (new_state == SYNC_STATE_DONE &&
            info->multipart_upload &&
            !info->end_multipart_upload) {
            commit_repo (task);
            return;
        }

        if (!(task->state == SYNC_STATE_DONE && new_state == SYNC_STATE_INIT) &&
            !(task->state == SYNC_STATE_INIT && new_state == SYNC_STATE_DONE)) {
            seaf_message ("Repo '%s' sync state transition from '%s' to '%s'.\n",
                          task->repo->name,
                          sync_state_str[task->state],
                          sync_state_str[new_state]);
        }

        task->state = new_state;
        if (new_state == SYNC_STATE_DONE || 
            new_state == SYNC_STATE_CANCELED ||
            new_state == SYNC_STATE_ERROR) {
            info->in_sync = FALSE;
            --(task->mgr->n_running_tasks);
            update_sync_info_error_state (task, new_state);

            /* Keep previous upload progress if sync task is canceled or failed. */
            if (new_state == SYNC_STATE_DONE) {
                info->multipart_upload = FALSE;
                info->end_multipart_upload = FALSE;
                info->total_bytes = 0;
                info->uploaded_bytes = 0;
            }
        }

#ifdef WIN32
        seaf_sync_manager_add_refresh_path (seaf->sync_mgr, task->repo->worktree);
#endif
    }
}