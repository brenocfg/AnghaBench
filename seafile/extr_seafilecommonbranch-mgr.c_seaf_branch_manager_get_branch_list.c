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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  char gchar ;
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  db_lock; int /*<<< orphan*/ * db; } ;
typedef  TYPE_2__ SeafBranchManager ;
typedef  int /*<<< orphan*/  SeafBranch ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_ERROR ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/ * g_list_prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_list_reverse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_branch_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * seaf_branch_new (char*,char const*,char*) ; 
 int /*<<< orphan*/  seaf_warning (char*,int,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite_query_prepare (int /*<<< orphan*/ *,char*) ; 

GList *
seaf_branch_manager_get_branch_list (SeafBranchManager *mgr,
                                     const char *repo_id)
{
    sqlite3 *db = mgr->priv->db;
    
    int result;
    sqlite3_stmt *stmt;
    char sql[256];
    char *name;
    char *commit_id;
    GList *ret = NULL;
    SeafBranch *branch;

    snprintf (sql, 256, "SELECT name, commit_id FROM branch WHERE repo_id ='%s'",
              repo_id);

    pthread_mutex_lock (&mgr->priv->db_lock);

    if ( !(stmt = sqlite_query_prepare(db, sql)) ) {
        pthread_mutex_unlock (&mgr->priv->db_lock);
        return NULL;
    }

    while (1) {
        result = sqlite3_step (stmt);
        if (result == SQLITE_ROW) {
            name = (char *)sqlite3_column_text(stmt, 0);
            commit_id = (char *)sqlite3_column_text(stmt, 1);
            branch = seaf_branch_new (name, repo_id, commit_id);
            ret = g_list_prepend (ret, branch);
        }
        if (result == SQLITE_DONE)
            break;
        if (result == SQLITE_ERROR) {
            const gchar *str = sqlite3_errmsg (db);
            seaf_warning ("Couldn't prepare query, error: %d->'%s'\n", 
                       result, str ? str : "no error given");
            sqlite3_finalize (stmt);
            seaf_branch_list_free (ret);
            pthread_mutex_unlock (&mgr->priv->db_lock);
            return NULL;
        }
    }

    sqlite3_finalize (stmt);
    pthread_mutex_unlock (&mgr->priv->db_lock);
    return g_list_reverse(ret);
}