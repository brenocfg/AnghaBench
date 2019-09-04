#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
struct TYPE_35__ {int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_34__ {TYPE_5__* data; struct TYPE_34__* next; } ;
struct TYPE_33__ {int worktree_invalid; scalar_t__ version; scalar_t__ sync_interval; int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/  auto_sync; int /*<<< orphan*/ * head; int /*<<< orphan*/  token; } ;
struct TYPE_32__ {TYPE_2__* priv; TYPE_1__* seaf; } ;
struct TYPE_31__ {scalar_t__ sync_perm_err_cnt; scalar_t__ in_sync; } ;
struct TYPE_30__ {int /*<<< orphan*/  auto_sync_enabled; } ;
struct TYPE_29__ {int /*<<< orphan*/  repo_mgr; } ;
typedef  TYPE_3__ SyncInfo ;
typedef  TYPE_4__ SeafSyncManager ;
typedef  TYPE_5__ SeafRepo ;
typedef  TYPE_6__ GList ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ SYNC_PERM_ERROR_RETRY_TIME ; 
 int TRUE ; 
 int /*<<< orphan*/  auto_delete_repo (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  check_folder_permissions (TYPE_4__*,TYPE_6__*) ; 
 scalar_t__ check_http_protocol (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  check_server_locked_files (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  cmp_repos_by_sync_time ; 
 int /*<<< orphan*/  g_list_free (TYPE_6__*) ; 
 TYPE_6__* g_list_sort_with_data (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* get_sync_info (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ periodic_sync_due (TYPE_5__*) ; 
 TYPE_9__* seaf ; 
 int /*<<< orphan*/  seaf_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ seaf_repo_check_worktree (TYPE_5__*) ; 
 TYPE_6__* seaf_repo_manager_get_repo_list (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  seaf_repo_manager_invalidate_repo_worktree (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  seaf_repo_manager_validate_repo_worktree (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seafile_session_config_get_allow_invalid_worktree (TYPE_9__*) ; 
 int /*<<< orphan*/  sync_repo_v2 (TYPE_4__*,TYPE_5__*,int) ; 

__attribute__((used)) static int
auto_sync_pulse (void *vmanager)
{
    SeafSyncManager *manager = vmanager;
    GList *repos, *ptr;
    SeafRepo *repo;

    repos = seaf_repo_manager_get_repo_list (manager->seaf->repo_mgr, -1, -1);

    check_folder_permissions (manager, repos);

    check_server_locked_files (manager, repos);

    /* Sort repos by last_sync_time, so that we don't "starve" any repo. */
    repos = g_list_sort_with_data (repos, cmp_repos_by_sync_time, NULL);

    for (ptr = repos; ptr != NULL; ptr = ptr->next) {
        repo = ptr->data;

        /* Every second, we'll check the worktree to see if it still exists.
         * We'll invalidate worktree if it gets moved or deleted.
         * But there is a hole here: If the user delete the worktree dir and
         * recreate a dir with the same name within a second, we'll falsely
         * see the worktree as valid. What's worse, the new worktree dir won't
         * be monitored.
         * This problem can only be solved by restart.
         */
        /* If repo has been checked out and the worktree doesn't exist,
         * we'll delete the repo automatically.
         */

        if (repo->head != NULL) {
            if (seaf_repo_check_worktree (repo) < 0) {
                if (!repo->worktree_invalid) {
                    // The repo worktree was valid, but now it's invalid
                    seaf_repo_manager_invalidate_repo_worktree (seaf->repo_mgr, repo);
                    if (!seafile_session_config_get_allow_invalid_worktree(seaf)) {
                        auto_delete_repo (manager, repo);
                    }
                }
                continue;
            } else {
                if (repo->worktree_invalid) {
                    // The repo worktree was invalid, but now it's valid again,
                    // so we start watch it
                    seaf_repo_manager_validate_repo_worktree (seaf->repo_mgr, repo);
                    continue;
                }
            }
        }

        repo->worktree_invalid = FALSE;

#ifdef USE_GPL_CRYPTO
        if (repo->version == 0 || (repo->encrypted && repo->enc_version < 2)) {
            continue;
        }
#endif

        if (!repo->token) {
            /* If the user has logged out of the account, the repo token would
             * be null */
            seaf_debug ("repo token of %s (%.8s) is null, would not sync it\n", repo->name, repo->id);
            continue;
        }

        /* Don't sync repos not checked out yet. */
        if (!repo->head)
            continue;

        if (!manager->priv->auto_sync_enabled || !repo->auto_sync)
            continue;

#if defined WIN32 || defined __APPLE__
        if (repo->version > 0) {
            if (repo->checking_locked_files)
                continue;

            gint64 now = (gint64)time(NULL);
            if (repo->last_check_locked_time == 0 ||
                now - repo->last_check_locked_time >= CHECK_LOCKED_FILES_INTERVAL)
            {
                repo->checking_locked_files = TRUE;
                if (seaf_job_manager_schedule_job (seaf->job_mgr,
                                                   check_locked_files,
                                                   check_locked_files_done,
                                                   repo) < 0) {
                    seaf_warning ("Failed to schedule check local locked files\n");
                    repo->checking_locked_files = FALSE;
                } else {
                    repo->last_check_locked_time = now;
                }

            }
        }
#endif

        SyncInfo *info = get_sync_info (manager, repo->id);

        if (info->in_sync)
            continue;

        if (info->sync_perm_err_cnt > SYNC_PERM_ERROR_RETRY_TIME)
            continue;

        if (repo->version > 0) {
            /* For repo version > 0, only use http sync. */
            if (check_http_protocol (manager, repo)) {
                if (repo->sync_interval == 0)
                    sync_repo_v2 (manager, repo, FALSE);
                else if (periodic_sync_due (repo))
                    sync_repo_v2 (manager, repo, TRUE);
            }
        } else {
            seaf_warning ("Repo %s(%s) is version 0 library. Syncing is no longer supported.\n",
                          repo->name, repo->id);
        }
    }

    g_list_free (repos);
    return TRUE;
}