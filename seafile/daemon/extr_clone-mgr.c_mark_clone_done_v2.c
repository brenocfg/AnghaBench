#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ server_url; scalar_t__ sync_wt_name; scalar_t__ is_readonly; int /*<<< orphan*/  passwd; int /*<<< orphan*/  worktree; } ;
struct TYPE_15__ {scalar_t__ sync_interval; TYPE_1__* head; int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/  worktree; scalar_t__ auto_sync; int /*<<< orphan*/  server_url; scalar_t__ encrypted; int /*<<< orphan*/  manager; } ;
struct TYPE_14__ {char* commit_id; } ;
struct TYPE_13__ {int /*<<< orphan*/  repo_mgr; int /*<<< orphan*/  wt_monitor; int /*<<< orphan*/  branch_mgr; } ;
typedef  TYPE_2__ SeafRepo ;
typedef  int /*<<< orphan*/  SeafBranch ;
typedef  TYPE_3__ CloneTask ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE_STATE_DONE ; 
 int /*<<< orphan*/  REPO_LOCAL_HEAD ; 
 int /*<<< orphan*/  REPO_REMOTE_HEAD ; 
 int /*<<< orphan*/  REPO_SYNC_WORKTREE_NAME ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_GENERAL_ERROR ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_LOCAL_DATA_CORRUPT ; 
 int /*<<< orphan*/  g_strdup (scalar_t__) ; 
 TYPE_10__* seaf ; 
 int /*<<< orphan*/ * seaf_branch_manager_get_branch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seaf_branch_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ seaf_repo_manager_set_repo_passwd (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_repo_manager_set_repo_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seaf_repo_manager_set_repo_worktree (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_repo_set_head (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_repo_set_readonly (TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ seaf_wt_monitor_watch_repo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transition_state (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transition_to_error (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mark_clone_done_v2 (SeafRepo *repo, CloneTask *task)
{
    SeafBranch *local = NULL;

    seaf_repo_manager_set_repo_worktree (repo->manager,
                                         repo,
                                         task->worktree);

    local = seaf_branch_manager_get_branch (seaf->branch_mgr, repo->id, "local");
    if (!local) {
        seaf_warning ("Cannot get branch local for repo %s(%.10s).\n",
                      repo->name, repo->id);
        transition_to_error (task, SYNC_ERROR_ID_LOCAL_DATA_CORRUPT);
        return;
    }
    /* Set repo head to mark checkout done. */
    seaf_repo_set_head (repo, local);
    seaf_branch_unref (local);

    if (repo->encrypted) {
        if (seaf_repo_manager_set_repo_passwd (seaf->repo_mgr,
                                               repo,
                                               task->passwd) < 0) {
            seaf_warning ("[Clone mgr] failed to set passwd for %s.\n", repo->id);
            transition_to_error (task, SYNC_ERROR_ID_GENERAL_ERROR);
            return;
        }
    }

    if (task->is_readonly) {
        seaf_repo_set_readonly (repo);
    }

    if (task->sync_wt_name) {
        seaf_repo_manager_set_repo_property (seaf->repo_mgr,
                                             repo->id,
                                             REPO_SYNC_WORKTREE_NAME,
                                             "true");
    }

    if (task->server_url)
        repo->server_url = g_strdup(task->server_url);

    if (repo->auto_sync && (repo->sync_interval == 0)) {
        if (seaf_wt_monitor_watch_repo (seaf->wt_monitor,
                                        repo->id, repo->worktree) < 0) {
            seaf_warning ("failed to watch repo %s(%.10s).\n", repo->name, repo->id);
            transition_to_error (task, SYNC_ERROR_ID_GENERAL_ERROR);
            return;
        }
    }

    /* For compatibility, still set these two properties.
     * So that if we downgrade to an old version, the syncing can still work.
     */
    seaf_repo_manager_set_repo_property (seaf->repo_mgr,
                                         repo->id,
                                         REPO_REMOTE_HEAD,
                                         repo->head->commit_id);
    seaf_repo_manager_set_repo_property (seaf->repo_mgr,
                                         repo->id,
                                         REPO_LOCAL_HEAD,
                                         repo->head->commit_id);

    transition_state (task, CLONE_STATE_DONE);
}