#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gboolean ;
struct TYPE_15__ {int /*<<< orphan*/  filelock_mgr; int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_14__ {int /*<<< orphan*/  synced_tree; int /*<<< orphan*/  syncing_tree; int /*<<< orphan*/  paths; } ;
struct TYPE_13__ {TYPE_1__* priv; } ;
struct TYPE_12__ {scalar_t__ in_error; } ;
struct TYPE_11__ {int /*<<< orphan*/  paths_lock; int /*<<< orphan*/  active_paths; } ;
typedef  size_t SyncStatus ;
typedef  TYPE_2__ SyncInfo ;
typedef  TYPE_3__ SeafSyncManager ;
typedef  TYPE_4__ ActivePathsInfo ;

/* Variables and functions */
 size_t SYNC_STATUS_LOCKED ; 
 size_t SYNC_STATUS_LOCKED_BY_ME ; 
 size_t SYNC_STATUS_NONE ; 
 size_t SYNC_STATUS_READONLY ; 
 size_t SYNC_STATUS_SYNCED ; 
 size_t SYNC_STATUS_SYNCING ; 
 TYPE_4__* g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 char* get_repo_sync_status (TYPE_3__*,char const*) ; 
 TYPE_2__* get_sync_info (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/ * path_status_tbl ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_6__* seaf ; 
 scalar_t__ seaf_filelock_manager_is_file_locked (int /*<<< orphan*/ ,char const*,char const*) ; 
 scalar_t__ seaf_filelock_manager_is_file_locked_by_me (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  seaf_repo_manager_is_path_writable (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 
 scalar_t__ sync_status_tree_exists (int /*<<< orphan*/ ,char const*) ; 

char *
seaf_sync_manager_get_path_sync_status (SeafSyncManager *mgr,
                                        const char *repo_id,
                                        const char *path,
                                        gboolean is_dir)
{
    ActivePathsInfo *info;
    SyncInfo *sync_info;
    SyncStatus ret = SYNC_STATUS_NONE;

    if (!repo_id || !path) {
        seaf_warning ("BUG: empty repo_id or path.\n");
        return NULL;
    }

    if (path[0] == 0) {
        return get_repo_sync_status (mgr, repo_id);
    }

    /* If the repo is in error, all files in it should show no sync status. */
    sync_info = get_sync_info (mgr, repo_id);
    if (sync_info && sync_info->in_error) {
        ret = SYNC_STATUS_NONE;
        goto out;
    }

    pthread_mutex_lock (&mgr->priv->paths_lock);

    info = g_hash_table_lookup (mgr->priv->active_paths, repo_id);
    if (!info) {
        pthread_mutex_unlock (&mgr->priv->paths_lock);
        ret = SYNC_STATUS_NONE;
        goto out;
    }

    ret = (SyncStatus) g_hash_table_lookup (info->paths, path);
    if (is_dir && (ret == SYNC_STATUS_NONE)) {
        /* If a dir is not in the syncing tree but in the synced tree,
         * it's synced. Otherwise if it's in the syncing tree, some files
         * under it must be syncing, so it should be in syncing status too.
         */
        if (sync_status_tree_exists (info->syncing_tree, path))
            ret = SYNC_STATUS_SYNCING;
        else if (sync_status_tree_exists (info->synced_tree, path))
            ret = SYNC_STATUS_SYNCED;
    }

    pthread_mutex_unlock (&mgr->priv->paths_lock);

    if (ret == SYNC_STATUS_SYNCED) {
        if (!seaf_repo_manager_is_path_writable(seaf->repo_mgr, repo_id, path))
            ret = SYNC_STATUS_READONLY;
        else if (seaf_filelock_manager_is_file_locked_by_me (seaf->filelock_mgr,
                                                             repo_id, path))
            ret = SYNC_STATUS_LOCKED_BY_ME;
        else if (seaf_filelock_manager_is_file_locked (seaf->filelock_mgr,
                                                       repo_id, path))
            ret = SYNC_STATUS_LOCKED;
    }

out:
    return g_strdup(path_status_tbl[ret]);
}