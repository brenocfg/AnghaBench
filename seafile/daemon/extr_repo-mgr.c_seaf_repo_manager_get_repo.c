#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_9__ {int /*<<< orphan*/  delete_pending; } ;
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  repo_hash; } ;
typedef  TYPE_2__ SeafRepoManager ;
typedef  TYPE_3__ SeafRepo ;

/* Variables and functions */
 TYPE_3__* g_hash_table_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 

SeafRepo*
seaf_repo_manager_get_repo (SeafRepoManager *manager, const gchar *id)
{
    SeafRepo *res;

    if (pthread_rwlock_rdlock (&manager->priv->lock) < 0) {
        seaf_warning ("[repo mgr] failed to lock repo cache.\n");
        return NULL;
    }

    res = g_hash_table_lookup (manager->priv->repo_hash, id);

    pthread_rwlock_unlock (&manager->priv->lock);

    if (res && !res->delete_pending)
        return res;

    return NULL;
}