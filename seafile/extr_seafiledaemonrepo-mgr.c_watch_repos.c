#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* gpointer ;
struct TYPE_12__ {int /*<<< orphan*/  wt_monitor; } ;
struct TYPE_11__ {TYPE_1__* priv; } ;
struct TYPE_10__ {scalar_t__ sync_interval; int /*<<< orphan*/  id; int /*<<< orphan*/  worktree; int /*<<< orphan*/  worktree_invalid; scalar_t__ auto_sync; } ;
struct TYPE_9__ {int /*<<< orphan*/  repo_hash; } ;
typedef  TYPE_3__ SeafRepoManager ;
typedef  TYPE_2__ SeafRepo ;
typedef  int /*<<< orphan*/  GHashTableIter ;

/* Variables and functions */
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,TYPE_2__**,TYPE_2__**) ; 
 TYPE_6__* seaf ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ seaf_wt_monitor_watch_repo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
watch_repos (SeafRepoManager *mgr)
{
    GHashTableIter iter;
    SeafRepo *repo;
    gpointer key, value;

    g_hash_table_iter_init (&iter, mgr->priv->repo_hash);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        repo = value;
        if (repo->auto_sync && !repo->worktree_invalid && (repo->sync_interval == 0)) {
            if (seaf_wt_monitor_watch_repo (seaf->wt_monitor, repo->id, repo->worktree) < 0) {
                seaf_warning ("failed to watch repo %s.\n", repo->id);
                /* If we fail to add watch at the beginning, sync manager
                 * will periodically check repo status and retry.
                 */
            }
        }
    }
}