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
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  repo_mgr; int /*<<< orphan*/  started; } ;
struct TYPE_10__ {scalar_t__ version; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {scalar_t__ in_sync; } ;
typedef  TYPE_1__ SyncInfo ;
typedef  int /*<<< orphan*/  SeafSyncManager ;
typedef  TYPE_2__ SeafRepo ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAF_ERR_BAD_REPO ; 
 int /*<<< orphan*/  SEAF_ERR_NO_WORKTREE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ check_http_protocol (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* get_sync_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__* seaf ; 
 int /*<<< orphan*/  seaf_message (char*) ; 
 scalar_t__ seaf_repo_check_worktree (TYPE_2__*) ; 
 TYPE_2__* seaf_repo_manager_get_repo (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,...) ; 
 int /*<<< orphan*/  sync_repo_v2 (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

int
seaf_sync_manager_add_sync_task (SeafSyncManager *mgr,
                                 const char *repo_id,
                                 GError **error)
{
    if (!seaf->started) {
        seaf_message ("sync manager is not started, skip sync request.\n");
        return -1;
    }

    SeafRepo *repo;

    repo = seaf_repo_manager_get_repo (seaf->repo_mgr, repo_id);
    if (!repo) {
        seaf_warning ("[sync mgr] cannot find repo %s.\n", repo_id);
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_REPO, "Invalid repo");
        return -1;
    }

    if (seaf_repo_check_worktree (repo) < 0) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_NO_WORKTREE,
                     "Worktree doesn't exist");
        return -1;
    }

#ifdef USE_GPL_CRYPTO
    if (repo->version == 0 || (repo->encrypted && repo->enc_version < 2)) {
        seaf_warning ("Don't support syncing old version libraries.\n");
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS,
                     "Don't support syncing old version libraries");
        return -1;
    }
#endif

    SyncInfo *info = get_sync_info (mgr, repo->id);

    if (info->in_sync)
        return 0;

    if (repo->version > 0) {
        if (check_http_protocol (mgr, repo)) {
            sync_repo_v2 (mgr, repo, TRUE);
            return 0;
        }
    } else {
        seaf_warning ("Repo %s(%s) is version 0 library. Syncing is no longer supported.\n",
                      repo->name, repo->id);
    }

    return 0;
}