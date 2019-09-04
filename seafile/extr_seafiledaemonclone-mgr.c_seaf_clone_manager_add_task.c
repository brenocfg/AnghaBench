#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_8__ {int /*<<< orphan*/  repo_mgr; int /*<<< orphan*/  sync_mgr; int /*<<< orphan*/  started; } ;
struct TYPE_7__ {int /*<<< orphan*/ * head; } ;
struct TYPE_6__ {scalar_t__ in_sync; } ;
typedef  TYPE_1__ SyncInfo ;
typedef  TYPE_2__ SeafRepo ;
typedef  int /*<<< orphan*/  SeafCloneManager ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAF_ERR_GENERAL ; 
 char* add_task_common (int /*<<< orphan*/ *,char const*,int,char const*,char const*,char const*,char const*,int,char const*,char*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  check_encryption_args (char const*,int,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_duplicate_task (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  is_wt_repo_name_same (char*,char const*) ; 
 char* make_worktree (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 TYPE_5__* seaf ; 
 int /*<<< orphan*/  seaf_clone_manager_check_worktree_path (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  seaf_message (char*) ; 
 TYPE_2__* seaf_repo_manager_get_repo (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  seaf_repo_manager_remove_garbage_repo (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  seaf_repo_manager_remove_repo_ondisk (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* seaf_sync_manager_get_sync_info (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ seafile_verify_repo_passwd (char const*,char const*,char const*,int) ; 

char *
seaf_clone_manager_add_task (SeafCloneManager *mgr, 
                             const char *repo_id,
                             int repo_version,
                             const char *peer_id,
                             const char *repo_name,
                             const char *token,
                             const char *passwd,
                             const char *magic,
                             int enc_version,
                             const char *random_key,
                             const char *worktree_in,
                             const char *peer_addr,
                             const char *peer_port,
                             const char *email,
                             const char *more_info,
                             GError **error)
{
    SeafRepo *repo;
    char *worktree;
    char *ret;
    gboolean sync_wt_name = FALSE;

    if (!seaf->started) {
        seaf_message ("System not started, skip adding clone task.\n");
        return NULL;
    }

#ifdef USE_GPL_CRYPTO
    if (repo_version == 0 || (passwd && enc_version < 2)) {
        seaf_warning ("Don't support syncing old version libraries.\n");
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS,
                     "Don't support syncing old version libraries");
        return NULL;
    }
#endif

    if (passwd &&
        !check_encryption_args (magic, enc_version, random_key, error))
        return NULL;

    /* After a repo was unsynced, the sync task may still be blocked in the
     * network, so the repo is not actually deleted yet.
     * In this case just return an error to the user.
     */
    SyncInfo *sync_info = seaf_sync_manager_get_sync_info (seaf->sync_mgr,
                                                           repo_id);
    if (sync_info && sync_info->in_sync) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_GENERAL,
                     "Repo already exists");
        return NULL;
    }

    repo = seaf_repo_manager_get_repo (seaf->repo_mgr, repo_id);

    if (repo != NULL && repo->head != NULL) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_GENERAL,
                     "Repo already exists");
        return NULL;
    }   

    if (is_duplicate_task (mgr, repo_id)) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_GENERAL, 
                     "Task is already in progress");
        return NULL;
    }

    if (passwd &&
        seafile_verify_repo_passwd(repo_id, passwd, magic, enc_version) < 0) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_GENERAL,
                     "Incorrect password");
        return NULL;
    }

    if (!seaf_clone_manager_check_worktree_path (mgr, worktree_in, error))
        return NULL;

    /* Return error if worktree_in conflicts with another repo or
     * is not a directory.
     */
    worktree = make_worktree (mgr, worktree_in, FALSE, error);
    if (!worktree) {
        return NULL;
    }

    /* Don't sync worktree folder name with library name later if they're not the same
     * at the beginning.
     */
    sync_wt_name = is_wt_repo_name_same (worktree, repo_name);

    /* If a repo was unsynced and then downloaded again, there may be
     * a garbage record for this repo. We don't want the downloaded blocks
     * be removed by GC.
     */
    if (repo_version > 0)
        seaf_repo_manager_remove_garbage_repo (seaf->repo_mgr, repo_id);

    /* Delete orphan information in the db in case the repo was corrupt. */
    if (!repo)
        seaf_repo_manager_remove_repo_ondisk (seaf->repo_mgr, repo_id, FALSE);

    ret = add_task_common (mgr, repo_id, repo_version,
                           peer_id, repo_name, token, passwd,
                           enc_version, random_key,
                           worktree, peer_addr, peer_port,
                           email, more_info,
                           sync_wt_name,
                           error);
    g_free (worktree);

    return ret;
}