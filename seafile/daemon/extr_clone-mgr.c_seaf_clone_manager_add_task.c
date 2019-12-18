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
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_8__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ json_error_t ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_11__ {int /*<<< orphan*/  repo_mgr; int /*<<< orphan*/  sync_mgr; int /*<<< orphan*/  started; } ;
struct TYPE_10__ {int /*<<< orphan*/ * head; } ;
struct TYPE_9__ {scalar_t__ in_sync; } ;
typedef  TYPE_2__ SyncInfo ;
typedef  TYPE_3__ SeafRepo ;
typedef  int /*<<< orphan*/  SeafCloneManager ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAF_ERR_BAD_ARGS ; 
 int /*<<< orphan*/  SEAF_ERR_GENERAL ; 
 char* add_task_common (int /*<<< orphan*/ *,char const*,int,char const*,char const*,char const*,char const*,int,char const*,char*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  check_encryption_args (char const*,int,char const*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ is_duplicate_task (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  is_wt_repo_name_same (char*,char const*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loads (char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  json_string_value (int /*<<< orphan*/ *) ; 
 char* make_worktree (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 TYPE_6__* seaf ; 
 int /*<<< orphan*/  seaf_clone_manager_check_worktree_path (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  seaf_message (char*) ; 
 TYPE_3__* seaf_repo_manager_get_repo (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  seaf_repo_manager_remove_garbage_repo (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  seaf_repo_manager_remove_repo_ondisk (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* seaf_sync_manager_get_sync_info (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 
 scalar_t__ seafile_verify_repo_passwd (char const*,char const*,char const*,int,char*) ; 

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
    SeafRepo *repo = NULL;
    char *worktree = NULL;
    char *ret = NULL;
    gboolean sync_wt_name = FALSE;
    char *repo_salt = NULL;

    if (!seaf->started) {
        seaf_message ("System not started, skip adding clone task.\n");
        goto out;
    }

#ifdef USE_GPL_CRYPTO
    if (repo_version == 0 || (passwd && enc_version < 2)) {
        seaf_warning ("Don't support syncing old version libraries.\n");
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS,
                     "Don't support syncing old version libraries");
        goto out;
    }
#endif

    if (more_info) {
        json_error_t jerror;
        json_t *object;

        object = json_loads (more_info, 0, &jerror);
        if (!object) {
            seaf_warning ("Failed to load more sync info from json: %s.\n", jerror.text);
            goto out;
        }
        json_t *string = json_object_get (object, "repo_salt");
        if (string)
            repo_salt = g_strdup (json_string_value (string));
        json_decref (object);
    }

    if (passwd &&
        !check_encryption_args (magic, enc_version, random_key, repo_salt, error)) {
        goto out;
    }
    /* After a repo was unsynced, the sync task may still be blocked in the
     * network, so the repo is not actually deleted yet.
     * In this case just return an error to the user.
     */
    SyncInfo *sync_info = seaf_sync_manager_get_sync_info (seaf->sync_mgr,
                                                           repo_id);
    if (sync_info && sync_info->in_sync) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_GENERAL,
                     "Repo already exists");
        goto out;
    }

    repo = seaf_repo_manager_get_repo (seaf->repo_mgr, repo_id);

    if (repo != NULL && repo->head != NULL) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_GENERAL,
                     "Repo already exists");
        goto out;
    }   

    if (is_duplicate_task (mgr, repo_id)) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_GENERAL, 
                     "Task is already in progress");
        goto out;
    }

    if (passwd &&
        seafile_verify_repo_passwd(repo_id, passwd, magic, enc_version, repo_salt) < 0) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_GENERAL,
                     "Incorrect password");
        goto out;
    }

    if (!seaf_clone_manager_check_worktree_path (mgr, worktree_in, error))
        goto out;

    /* Return error if worktree_in conflicts with another repo or
     * is not a directory.
     */
    worktree = make_worktree (mgr, worktree_in, FALSE, error);
    if (!worktree) {
        goto out;
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

out:
    g_free (worktree);
    g_free (repo_salt);

    return ret;
}