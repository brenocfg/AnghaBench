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
typedef  void* gpointer ;
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  repo_locked_files; } ;
typedef  TYPE_2__ SeafFilelockManager ;
typedef  int /*<<< orphan*/  GHashTableIter ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 int /*<<< orphan*/  g_hash_table_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,void**,void**) ; 
 int /*<<< orphan*/  init_locks ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int
seaf_filelock_manager_start (SeafFilelockManager *mgr)
{
    GHashTableIter iter;
    gpointer key, value;
    char *repo_id;
    GHashTable *locks;

    pthread_mutex_lock (&mgr->priv->hash_lock);

    g_hash_table_iter_init (&iter, mgr->priv->repo_locked_files);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        repo_id = key;
        locks = value;
        g_hash_table_foreach (locks, init_locks, repo_id);
    }

    pthread_mutex_unlock (&mgr->priv->hash_lock);

    return 0;
}