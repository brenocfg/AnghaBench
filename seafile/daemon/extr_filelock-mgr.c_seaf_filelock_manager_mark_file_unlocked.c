#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  repo_locked_files; } ;
typedef  TYPE_2__ SeafFilelockManager ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 int /*<<< orphan*/ * g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  g_hash_table_remove (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refresh_locked_path_status (char const*,char const*) ; 
 int remove_locked_file_from_db (TYPE_2__*,char const*,char const*) ; 

int
seaf_filelock_manager_mark_file_unlocked (SeafFilelockManager *mgr,
                                          const char *repo_id,
                                          const char *path)
{
    GHashTable *locks;

    pthread_mutex_lock (&mgr->priv->hash_lock);

    locks = g_hash_table_lookup (mgr->priv->repo_locked_files, repo_id);
    if (!locks) {
        pthread_mutex_unlock (&mgr->priv->hash_lock);
        return 0;
    }

    g_hash_table_remove (locks, path);

    pthread_mutex_unlock (&mgr->priv->hash_lock);

#ifdef WIN32
    refresh_locked_path_status (repo_id, path);
#endif

    return remove_locked_file_from_db (mgr, repo_id, path);
}