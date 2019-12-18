#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  sync_mgr; } ;
struct TYPE_14__ {scalar_t__ version; int /*<<< orphan*/  id; } ;
struct TYPE_13__ {TYPE_1__* priv; } ;
struct TYPE_12__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  repo_hash; } ;
typedef  TYPE_2__ SeafRepoManager ;
typedef  TYPE_3__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_hash_table_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_repo_stores (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_folder_perms (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* seaf ; 
 int /*<<< orphan*/  seaf_repo_free (TYPE_3__*) ; 
 int /*<<< orphan*/  seaf_repo_manager_remove_repo_ondisk (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_sync_manager_remove_active_path_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 

int
seaf_repo_manager_del_repo (SeafRepoManager *mgr,
                            SeafRepo *repo)
{
    seaf_repo_manager_remove_repo_ondisk (mgr, repo->id,
                                          (repo->version > 0) ? TRUE : FALSE);

    seaf_sync_manager_remove_active_path_info (seaf->sync_mgr, repo->id);

    remove_folder_perms (mgr, repo->id);

    move_repo_stores (mgr, repo);

    if (pthread_rwlock_wrlock (&mgr->priv->lock) < 0) {
        seaf_warning ("[repo mgr] failed to lock repo cache.\n");
        return -1;
    }

    g_hash_table_remove (mgr->priv->repo_hash, repo->id);

    pthread_rwlock_unlock (&mgr->priv->lock);

    seaf_repo_free (repo);

    return 0;
}