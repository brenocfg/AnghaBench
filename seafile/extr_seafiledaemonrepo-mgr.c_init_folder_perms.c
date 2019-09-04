#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char* data; struct TYPE_12__* next; } ;
struct TYPE_11__ {TYPE_1__* priv; } ;
struct TYPE_10__ {int /*<<< orphan*/  perm_lock; void* group_perms; void* user_perms; int /*<<< orphan*/  repo_hash; } ;
typedef  TYPE_1__ SeafRepoManagerPriv ;
typedef  TYPE_2__ SeafRepoManager ;
typedef  TYPE_3__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  FOLDER_PERM_TYPE_GROUP ; 
 int /*<<< orphan*/  FOLDER_PERM_TYPE_USER ; 
 int /*<<< orphan*/  g_free ; 
 TYPE_3__* g_hash_table_get_keys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_hash_table_insert (void*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 void* g_hash_table_new_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_list_free (TYPE_3__*) ; 
 int /*<<< orphan*/  g_str_equal ; 
 int /*<<< orphan*/  g_str_hash ; 
 int /*<<< orphan*/  g_strdup (char*) ; 
 TYPE_3__* load_folder_perms_for_repo (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
init_folder_perms (SeafRepoManager *mgr)
{
    SeafRepoManagerPriv *priv = mgr->priv;
    GList *repo_ids = g_hash_table_get_keys (priv->repo_hash);
    GList *ptr;
    GList *perms;
    char *repo_id;

    priv->user_perms = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);
    priv->group_perms = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);
    pthread_mutex_init (&priv->perm_lock, NULL);

    for (ptr = repo_ids; ptr; ptr = ptr->next) {
        repo_id = ptr->data;
        perms = load_folder_perms_for_repo (mgr, repo_id, FOLDER_PERM_TYPE_USER);
        if (perms) {
            pthread_mutex_lock (&priv->perm_lock);
            g_hash_table_insert (priv->user_perms, g_strdup(repo_id), perms);
            pthread_mutex_unlock (&priv->perm_lock);
        }
        perms = load_folder_perms_for_repo (mgr, repo_id, FOLDER_PERM_TYPE_GROUP);
        if (perms) {
            pthread_mutex_lock (&priv->perm_lock);
            g_hash_table_insert (priv->group_perms, g_strdup(repo_id), perms);
            pthread_mutex_unlock (&priv->perm_lock);
        }
    }

    g_list_free (repo_ids);
}