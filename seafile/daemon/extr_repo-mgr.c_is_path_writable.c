#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int gboolean ;
struct TYPE_6__ {TYPE_2__* repo_mgr; } ;
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  perm_lock; int /*<<< orphan*/  group_perms; int /*<<< orphan*/  user_perms; } ;
typedef  TYPE_2__ SeafRepoManager ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/ * g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 
 char* g_strconcat (char*,char const*,int /*<<< orphan*/ *) ; 
 char* lookup_folder_perm (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* seaf ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static gboolean
is_path_writable (const char *repo_id,
                  gboolean is_repo_readonly,
                  const char *path)
{
    SeafRepoManager *mgr = seaf->repo_mgr;
    GList *user_perms = NULL, *group_perms = NULL;
    char *permission = NULL;
    char *abs_path = NULL;

    pthread_mutex_lock (&mgr->priv->perm_lock);

    user_perms = g_hash_table_lookup (mgr->priv->user_perms, repo_id);
    group_perms = g_hash_table_lookup (mgr->priv->group_perms, repo_id);

    if (user_perms || group_perms)
        abs_path = g_strconcat ("/", path, NULL);

    if (user_perms)
        permission = lookup_folder_perm (user_perms, abs_path);
    if (!permission && group_perms)
        permission = lookup_folder_perm (group_perms, abs_path);

    pthread_mutex_unlock (&mgr->priv->perm_lock);

    g_free (abs_path);

    if (!permission)
        return !is_repo_readonly;

    if (strcmp (permission, "rw") == 0)
        return TRUE;
    else
        return FALSE;
}