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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_8__ {int /*<<< orphan*/  delete_pending; } ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  repo_hash; } ;
typedef  TYPE_2__ SeafRepoManager ;
typedef  TYPE_3__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* g_hash_table_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 

gboolean
seaf_repo_manager_repo_exists (SeafRepoManager *manager, const gchar *id)
{
    SeafRepo *res;

    if (pthread_rwlock_rdlock (&manager->priv->lock) < 0) {
        seaf_warning ("[repo mgr] failed to lock repo cache.\n");
        return FALSE;
    }

    res = g_hash_table_lookup (manager->priv->repo_hash, id);

    pthread_rwlock_unlock (&manager->priv->lock);

    if (res && !res->delete_pending)
        return TRUE;
    
    return FALSE;
}