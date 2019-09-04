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
typedef  int /*<<< orphan*/  sql ;
struct TYPE_12__ {scalar_t__ data; struct TYPE_12__* next; } ;
struct TYPE_11__ {TYPE_1__* priv; } ;
struct TYPE_10__ {int /*<<< orphan*/  db_lock; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ SeafRepoManager ;
typedef  TYPE_3__ GList ;
typedef  scalar_t__ FolderPermType ;
typedef  int /*<<< orphan*/  FolderPerm ;

/* Variables and functions */
 scalar_t__ FOLDER_PERM_TYPE_GROUP ; 
 scalar_t__ FOLDER_PERM_TYPE_USER ; 
 int /*<<< orphan*/  comp_folder_perms ; 
 int /*<<< orphan*/  folder_perm_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_list_free (TYPE_3__*) ; 
 TYPE_3__* g_list_sort (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_return_val_if_fail (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_folder_perm ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,char const*) ; 
 scalar_t__ sqlite_foreach_selected_row (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_3__**) ; 

__attribute__((used)) static GList *
load_folder_perms_for_repo (SeafRepoManager *mgr,
                            const char *repo_id,
                            FolderPermType type)
{
    GList *perms = NULL;
    char sql[256];

    g_return_val_if_fail ((type == FOLDER_PERM_TYPE_USER ||
                           type == FOLDER_PERM_TYPE_GROUP),
                          NULL);

    if (type == FOLDER_PERM_TYPE_USER)
        sqlite3_snprintf (sizeof(sql), sql,
                          "SELECT path, permission FROM FolderUserPerms "
                          "WHERE repo_id = '%q'",
                          repo_id);
    else
        sqlite3_snprintf (sizeof(sql), sql,
                          "SELECT path, permission FROM FolderGroupPerms "
                          "WHERE repo_id = '%q'",
                          repo_id);

    pthread_mutex_lock (&mgr->priv->db_lock);

    if (sqlite_foreach_selected_row (mgr->priv->db, sql,
                                     load_folder_perm, &perms) < 0) {
        pthread_mutex_unlock (&mgr->priv->db_lock);
        GList *ptr;
        for (ptr = perms; ptr; ptr = ptr->next)
            folder_perm_free ((FolderPerm *)ptr->data);
        g_list_free (perms);
        return NULL;
    }

    pthread_mutex_unlock (&mgr->priv->db_lock);

    /* Sort list in descending order by perm->path (longer path first). */
    perms = g_list_sort (perms, comp_folder_perms);

    return perms;
}