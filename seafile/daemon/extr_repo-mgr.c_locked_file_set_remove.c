#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_7__ {char const* repo_id; int /*<<< orphan*/  locked_files; TYPE_2__* mgr; } ;
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  db_lock; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ SeafRepoManager ;
typedef  TYPE_3__ LockedFileSet ;

/* Variables and functions */
 scalar_t__ SQLITE_DONE ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/ * g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  g_hash_table_remove (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_debug (char*,char const*,char const*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ *,int,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite_query_prepare (int /*<<< orphan*/ ,char*) ; 

int
locked_file_set_remove (LockedFileSet *fset, const char *path, gboolean db_only)
{
    SeafRepoManager *mgr = fset->mgr;
    char *sql;
    sqlite3_stmt *stmt;

    if (g_hash_table_lookup (fset->locked_files, path) == NULL)
        return 0;

    seaf_debug ("Remove locked file record %.8s, %s.\n",
                fset->repo_id, path);

    pthread_mutex_lock (&mgr->priv->db_lock);

    sql = "DELETE FROM LockedFiles WHERE repo_id = ? AND path = ?";
    stmt = sqlite_query_prepare (mgr->priv->db, sql);
    sqlite3_bind_text (stmt, 1, fset->repo_id, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text (stmt, 2, path, -1, SQLITE_TRANSIENT);
    if (sqlite3_step (stmt) != SQLITE_DONE) {
        seaf_warning ("Failed to remove locked file %s from db: %s.\n",
                      path, sqlite3_errmsg (mgr->priv->db));
        sqlite3_finalize (stmt);
        pthread_mutex_unlock (&mgr->priv->db_lock);
        return -1;
    }
    sqlite3_finalize (stmt);
    pthread_mutex_unlock (&mgr->priv->db_lock);

    if (!db_only)
        g_hash_table_remove (fset->locked_files, path);

    return 0;
}