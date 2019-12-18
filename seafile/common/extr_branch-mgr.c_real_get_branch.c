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
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  db_lock; int /*<<< orphan*/ * db; } ;
typedef  TYPE_2__ SeafBranchManager ;
typedef  int /*<<< orphan*/  SeafBranch ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * seaf_branch_new (char const*,char const*,char*) ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,char const*) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite_query_prepare (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static SeafBranch *
real_get_branch (SeafBranchManager *mgr,
                 const char *repo_id,
                 const char *name)
{
    SeafBranch *branch = NULL;
    sqlite3_stmt *stmt;
    sqlite3 *db;
    char *sql;
    int result;

    pthread_mutex_lock (&mgr->priv->db_lock);

    db = mgr->priv->db;
    sql = sqlite3_mprintf ("SELECT commit_id FROM Branch "
                           "WHERE name = %Q and repo_id='%s'",
                           name, repo_id);
    if (!(stmt = sqlite_query_prepare (db, sql))) {
        seaf_warning ("[Branch mgr] Couldn't prepare query %s\n", sql);
        sqlite3_free (sql);
        pthread_mutex_unlock (&mgr->priv->db_lock);
        return NULL;
    }
    sqlite3_free (sql);

    result = sqlite3_step (stmt);
    if (result == SQLITE_ROW) {
        char *commit_id = (char *)sqlite3_column_text (stmt, 0);

        branch = seaf_branch_new (name, repo_id, commit_id);
        pthread_mutex_unlock (&mgr->priv->db_lock);
        sqlite3_finalize (stmt);
        return branch;
    } else if (result == SQLITE_ERROR) {
        const char *str = sqlite3_errmsg (db);
        seaf_warning ("Couldn't prepare query, error: %d->'%s'\n",
                   result, str ? str : "no error given");
    }

    sqlite3_finalize (stmt);
    pthread_mutex_unlock (&mgr->priv->db_lock);
    return NULL;
}