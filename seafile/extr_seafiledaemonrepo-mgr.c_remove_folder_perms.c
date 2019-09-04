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
struct TYPE_4__ {int /*<<< orphan*/  perm_lock; int /*<<< orphan*/  group_perms; int /*<<< orphan*/  user_perms; } ;
typedef  TYPE_2__ SeafRepoManager ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  GDestroyNotify ;

/* Variables and functions */
 scalar_t__ folder_perm_free ; 
 int /*<<< orphan*/ * g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  g_hash_table_remove (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  g_list_free_full (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
remove_folder_perms (SeafRepoManager *mgr, const char *repo_id)
{
    GList *perms = NULL;

    pthread_mutex_lock (&mgr->priv->perm_lock);

    perms = g_hash_table_lookup (mgr->priv->user_perms, repo_id);
    if (perms) {
        g_list_free_full (perms, (GDestroyNotify)folder_perm_free);
        g_hash_table_remove (mgr->priv->user_perms, repo_id);
    }

    perms = g_hash_table_lookup (mgr->priv->group_perms, repo_id);
    if (perms) {
        g_list_free_full (perms, (GDestroyNotify)folder_perm_free);
        g_hash_table_remove (mgr->priv->group_perms, repo_id);
    }

    pthread_mutex_unlock (&mgr->priv->perm_lock);
}