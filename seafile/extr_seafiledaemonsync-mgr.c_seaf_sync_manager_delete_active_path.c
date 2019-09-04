#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  synced_tree; int /*<<< orphan*/  syncing_tree; int /*<<< orphan*/  paths; } ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  paths_lock; int /*<<< orphan*/  active_paths; } ;
typedef  TYPE_2__ SeafSyncManager ;
typedef  TYPE_3__ ActivePathsInfo ;

/* Variables and functions */
 TYPE_3__* g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  g_hash_table_remove (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 
 int /*<<< orphan*/  sync_status_tree_del (int /*<<< orphan*/ ,char const*) ; 

void
seaf_sync_manager_delete_active_path (SeafSyncManager *mgr,
                                      const char *repo_id,
                                      const char *path)
{
    ActivePathsInfo *info;

    if (!repo_id || !path) {
        seaf_warning ("BUG: empty repo_id or path.\n");
        return;
    }

    pthread_mutex_lock (&mgr->priv->paths_lock);

    info = g_hash_table_lookup (mgr->priv->active_paths, repo_id);
    if (!info) {
        pthread_mutex_unlock (&mgr->priv->paths_lock);
        return;
    }

    g_hash_table_remove (info->paths, path);
    sync_status_tree_del (info->syncing_tree, path);
    sync_status_tree_del (info->synced_tree, path);

    pthread_mutex_unlock (&mgr->priv->paths_lock);
}