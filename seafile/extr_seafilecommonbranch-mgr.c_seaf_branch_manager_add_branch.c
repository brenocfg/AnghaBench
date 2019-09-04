#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sql ;
struct TYPE_8__ {int /*<<< orphan*/  commit_id; int /*<<< orphan*/  repo_id; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  db_lock; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ SeafBranchManager ;
typedef  TYPE_3__ SeafBranch ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ sqlite_check_for_existence (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sqlite_query_exec (int /*<<< orphan*/ ,char*) ; 

int
seaf_branch_manager_add_branch (SeafBranchManager *mgr, SeafBranch *branch)
{
#ifndef SEAFILE_SERVER
    char sql[256];

    pthread_mutex_lock (&mgr->priv->db_lock);

    sqlite3_snprintf (sizeof(sql), sql,
                      "SELECT 1 FROM Branch WHERE name=%Q and repo_id=%Q",
                      branch->name, branch->repo_id);
    if (sqlite_check_for_existence (mgr->priv->db, sql))
        sqlite3_snprintf (sizeof(sql), sql,
                          "UPDATE Branch SET commit_id=%Q WHERE "
                          "name=%Q and repo_id=%Q",
                          branch->commit_id, branch->name, branch->repo_id);
    else
        sqlite3_snprintf (sizeof(sql), sql,
                          "INSERT INTO Branch VALUES (%Q, %Q, %Q)",
                          branch->name, branch->repo_id, branch->commit_id);

    sqlite_query_exec (mgr->priv->db, sql);

    pthread_mutex_unlock (&mgr->priv->db_lock);

    return 0;
#else
    char *sql;
    SeafDB *db = mgr->seaf->db;

    if (seaf_db_type(db) == SEAF_DB_TYPE_PGSQL) {
        gboolean exists, err;
        int rc;

        sql = "SELECT repo_id FROM Branch WHERE name=? AND repo_id=?";
        exists = seaf_db_statement_exists(db, sql, &err,
                                          2, "string", branch->name,
                                          "string", branch->repo_id);
        if (err)
            return -1;

        if (exists)
            rc = seaf_db_statement_query (db,
                                          "UPDATE Branch SET commit_id=? "
                                          "WHERE name=? AND repo_id=?",
                                          3, "string", branch->commit_id,
                                          "string", branch->name,
                                          "string", branch->repo_id);
        else
            rc = seaf_db_statement_query (db,
                                          "INSERT INTO Branch VALUES (?, ?, ?)",
                                          3, "string", branch->name,
                                          "string", branch->repo_id,
                                          "string", branch->commit_id);
        if (rc < 0)
            return -1;
    } else {
        int rc = seaf_db_statement_query (db,
                                 "REPLACE INTO Branch VALUES (?, ?, ?)",
                                 3, "string", branch->name,
                                 "string", branch->repo_id,
                                 "string", branch->commit_id);
        if (rc < 0)
            return -1;
    }
    return 0;
#endif
}