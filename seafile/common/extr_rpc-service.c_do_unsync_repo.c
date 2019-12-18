#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  repo_mgr; int /*<<< orphan*/  sync_mgr; int /*<<< orphan*/  wt_monitor; int /*<<< orphan*/  started; } ;
struct TYPE_9__ {scalar_t__ sync_interval; int /*<<< orphan*/  worktree; int /*<<< orphan*/  id; scalar_t__ auto_sync; } ;
struct TYPE_8__ {scalar_t__ in_sync; } ;
typedef  TYPE_1__ SyncInfo ;
typedef  TYPE_2__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 TYPE_6__* seaf ; 
 int /*<<< orphan*/  seaf_message (char*) ; 
 int /*<<< orphan*/  seaf_repo_manager_del_repo (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_repo_manager_mark_repo_deleted (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_sync_manager_cancel_sync_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* seaf_sync_manager_get_sync_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_wt_monitor_unwatch_repo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int do_unsync_repo(SeafRepo *repo)
{
    if (!seaf->started) {
        seaf_message ("System not started, skip removing repo.\n");
        return -1;
    }

    if (repo->auto_sync && (repo->sync_interval == 0))
        seaf_wt_monitor_unwatch_repo (seaf->wt_monitor, repo->id);

    seaf_sync_manager_cancel_sync_task (seaf->sync_mgr, repo->id);

    SyncInfo *info = seaf_sync_manager_get_sync_info (seaf->sync_mgr, repo->id);

    /* If we are syncing the repo,
     * we just mark the repo as deleted and let sync-mgr actually delete it.
     * Otherwise we are safe to delete the repo.
     */
    char *worktree = g_strdup (repo->worktree);
    if (info != NULL && info->in_sync) {
        seaf_repo_manager_mark_repo_deleted (seaf->repo_mgr, repo);
    } else {
        seaf_repo_manager_del_repo (seaf->repo_mgr, repo);
    }

    g_free (worktree);

    return 0;
}