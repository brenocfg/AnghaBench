#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_17__ {char const* path; char const* permission; } ;
struct TYPE_16__ {TYPE_4__* data; struct TYPE_16__* next; } ;
struct TYPE_15__ {TYPE_1__* priv; } ;
struct TYPE_14__ {int /*<<< orphan*/  perm_lock; int /*<<< orphan*/  group_perms; int /*<<< orphan*/  user_perms; int /*<<< orphan*/  db_lock; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ SeafRepoManager ;
typedef  TYPE_3__ GList ;
typedef  int /*<<< orphan*/  GDestroyNotify ;
typedef  scalar_t__ FolderPermType ;
typedef  TYPE_4__ FolderPerm ;

/* Variables and functions */
 scalar_t__ FOLDER_PERM_TYPE_GROUP ; 
 scalar_t__ FOLDER_PERM_TYPE_USER ; 
 scalar_t__ SQLITE_DONE ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  comp_folder_perms ; 
 scalar_t__ folder_perm_free ; 
 TYPE_3__* folder_perm_list_copy (TYPE_3__*) ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  g_list_free_full (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* g_list_sort (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_return_val_if_fail (int,int) ; 
 int /*<<< orphan*/  g_strdup (char const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ *,int,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_clear_bindings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite_query_prepare (int /*<<< orphan*/ ,char*) ; 

int
seaf_repo_manager_update_folder_perms (SeafRepoManager *mgr,
                                       const char *repo_id,
                                       FolderPermType type,
                                       GList *folder_perms)
{
    char *sql;
    sqlite3_stmt *stmt;
    GList *ptr;
    FolderPerm *perm;

    g_return_val_if_fail ((type == FOLDER_PERM_TYPE_USER ||
                           type == FOLDER_PERM_TYPE_GROUP),
                          -1);

    /* Update db. */

    pthread_mutex_lock (&mgr->priv->db_lock);

    if (type == FOLDER_PERM_TYPE_USER)
        sql = "DELETE FROM FolderUserPerms WHERE repo_id = ?";
    else
        sql = "DELETE FROM FolderGroupPerms WHERE repo_id = ?";
    stmt = sqlite_query_prepare (mgr->priv->db, sql);
    sqlite3_bind_text (stmt, 1, repo_id, -1, SQLITE_TRANSIENT);
    if (sqlite3_step (stmt) != SQLITE_DONE) {
        seaf_warning ("Failed to remove folder perms for %.8s: %s.\n",
                      repo_id, sqlite3_errmsg (mgr->priv->db));
        sqlite3_finalize (stmt);
        pthread_mutex_unlock (&mgr->priv->db_lock);
        return -1;
    }
    sqlite3_finalize (stmt);

    if (!folder_perms) {
        pthread_mutex_unlock (&mgr->priv->db_lock);
        return 0;
    }

    if (type == FOLDER_PERM_TYPE_USER)
        sql = "INSERT INTO FolderUserPerms VALUES (?, ?, ?)";
    else
        sql = "INSERT INTO FolderGroupPerms VALUES (?, ?, ?)";
    stmt = sqlite_query_prepare (mgr->priv->db, sql);

    for (ptr = folder_perms; ptr; ptr = ptr->next) {
        perm = ptr->data;

        sqlite3_bind_text (stmt, 1, repo_id, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text (stmt, 2, perm->path, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text (stmt, 3, perm->permission, -1, SQLITE_TRANSIENT);

        if (sqlite3_step (stmt) != SQLITE_DONE) {
            seaf_warning ("Failed to insert folder perms for %.8s: %s.\n",
                          repo_id, sqlite3_errmsg (mgr->priv->db));
            sqlite3_finalize (stmt);
            pthread_mutex_unlock (&mgr->priv->db_lock);
            return -1;
        }

        sqlite3_reset (stmt);
        sqlite3_clear_bindings (stmt);
    }

    sqlite3_finalize (stmt);

    pthread_mutex_unlock (&mgr->priv->db_lock);

    /* Update in memory */
    GList *new, *old;
    new = folder_perm_list_copy (folder_perms);
    new = g_list_sort (new, comp_folder_perms);

    pthread_mutex_lock (&mgr->priv->perm_lock);
    if (type == FOLDER_PERM_TYPE_USER) {
        old = g_hash_table_lookup (mgr->priv->user_perms, repo_id);
        if (old)
            g_list_free_full (old, (GDestroyNotify)folder_perm_free);
        g_hash_table_insert (mgr->priv->user_perms, g_strdup(repo_id), new);
    } else if (type == FOLDER_PERM_TYPE_GROUP) {
        old = g_hash_table_lookup (mgr->priv->group_perms, repo_id);
        if (old)
            g_list_free_full (old, (GDestroyNotify)folder_perm_free);
        g_hash_table_insert (mgr->priv->group_perms, g_strdup(repo_id), new);
    }
    pthread_mutex_unlock (&mgr->priv->perm_lock);

    return 0;
}