#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int gint ;
typedef  void* gboolean ;
struct TYPE_12__ {scalar_t__ last_check; scalar_t__ partial_commit; int /*<<< orphan*/  last_changed; } ;
typedef  TYPE_2__ WTStatus ;
struct TYPE_14__ {void* create_partial_commit; int /*<<< orphan*/  id; } ;
struct TYPE_13__ {TYPE_1__* seaf; } ;
struct TYPE_11__ {int /*<<< orphan*/  wt_monitor; } ;
typedef  int /*<<< orphan*/  SyncTask ;
typedef  TYPE_3__ SeafSyncManager ;
typedef  TYPE_4__ SeafRepo ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  commit_repo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_sync_task_v2 (TYPE_3__*,TYPE_4__*,void*,void*) ; 
 int g_atomic_int_get (int /*<<< orphan*/ *) ; 
 TYPE_2__* seaf_wt_monitor_get_worktree_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wt_status_unref (TYPE_2__*) ; 

__attribute__((used)) static gboolean
create_commit_from_event_queue (SeafSyncManager *manager, SeafRepo *repo,
                                gboolean is_manual_sync)
{
    WTStatus *status;
    SyncTask *task;
    gboolean ret = FALSE;
    gint now = (gint)time(NULL);
    gint last_changed;

    status = seaf_wt_monitor_get_worktree_status (manager->seaf->wt_monitor,
                                                  repo->id);
    if (status) {
        last_changed = g_atomic_int_get (&status->last_changed);
        if (status->last_check == 0) {
            /* Force commit and sync after a new repo is added. */
            task = create_sync_task_v2 (manager, repo, is_manual_sync, TRUE);
            repo->create_partial_commit = TRUE;
            commit_repo (task);
            status->last_check = now;
            ret = TRUE;
        } else if (status->partial_commit) {
            task = create_sync_task_v2 (manager, repo, is_manual_sync, FALSE);
            repo->create_partial_commit = TRUE;
            commit_repo (task);
            ret = TRUE;
        } else if (last_changed != 0 && status->last_check <= last_changed) {
            /* Commit and sync if the repo has been updated after the
             * last check and is not updated for the last 2 seconds.
             */
            if (now - last_changed >= 2) {
                task = create_sync_task_v2 (manager, repo, is_manual_sync, FALSE);
                repo->create_partial_commit = TRUE;
                commit_repo (task);
                status->last_check = now;
                ret = TRUE;
            }
        }
        wt_status_unref (status);
    }

    return ret;
}