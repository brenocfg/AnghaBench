#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* gpointer ;
struct TYPE_11__ {TYPE_1__* priv; } ;
struct TYPE_10__ {int /*<<< orphan*/  delete_pending; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  repo_hash; } ;
typedef  TYPE_3__ SeafRepoManager ;
typedef  TYPE_2__ SeafRepo ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  GHashTableIter ;

/* Variables and functions */
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,TYPE_2__**,TYPE_2__**) ; 
 int /*<<< orphan*/ * g_list_prepend (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 

GList*
seaf_repo_manager_get_repo_list (SeafRepoManager *manager, int start, int limit)
{
    GList *repo_list = NULL;
    GHashTableIter iter;
    SeafRepo *repo;
    gpointer key, value;

    if (pthread_rwlock_rdlock (&manager->priv->lock) < 0) {
        seaf_warning ("[repo mgr] failed to lock repo cache.\n");
        return NULL;
    }
    g_hash_table_iter_init (&iter, manager->priv->repo_hash);

    while (g_hash_table_iter_next (&iter, &key, &value)) {
        repo = value;
        if (!repo->delete_pending)
            repo_list = g_list_prepend (repo_list, repo);
    }

    pthread_rwlock_unlock (&manager->priv->lock);

    return repo_list;
}