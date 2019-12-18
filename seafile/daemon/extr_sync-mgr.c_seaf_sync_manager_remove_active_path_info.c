#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  paths_lock; int /*<<< orphan*/  active_paths; } ;
typedef  TYPE_2__ SeafSyncManager ;

/* Variables and functions */
 int /*<<< orphan*/  SHCNE_ASSOCCHANGED ; 
 int /*<<< orphan*/  SHCNF_IDLIST ; 
 int /*<<< orphan*/  SHChangeNotify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_remove (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void
seaf_sync_manager_remove_active_path_info (SeafSyncManager *mgr, const char *repo_id)
{
    pthread_mutex_lock (&mgr->priv->paths_lock);

    g_hash_table_remove (mgr->priv->active_paths, repo_id);

    pthread_mutex_unlock (&mgr->priv->paths_lock);

#ifdef WIN32
    /* This is a hack to tell Windows Explorer to refresh all open windows. */
    SHChangeNotify (SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
#endif
}