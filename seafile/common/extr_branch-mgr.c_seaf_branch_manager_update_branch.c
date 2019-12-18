#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_10__ {int /*<<< orphan*/  repo_id; int /*<<< orphan*/  name; int /*<<< orphan*/  commit_id; } ;
struct TYPE_9__ {TYPE_2__* seaf; TYPE_1__* priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  db; } ;
struct TYPE_7__ {int /*<<< orphan*/  db_lock; int /*<<< orphan*/ * db; } ;
typedef  TYPE_3__ SeafBranchManager ;
typedef  TYPE_4__ SeafBranch ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int seaf_db_statement_query (int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite_query_exec (int /*<<< orphan*/ *,char*) ; 

int
seaf_branch_manager_update_branch (SeafBranchManager *mgr, SeafBranch *branch)
{
#ifndef SEAFILE_SERVER
    sqlite3 *db;
    char *sql;

    pthread_mutex_lock (&mgr->priv->db_lock);

    db = mgr->priv->db;
    sql = sqlite3_mprintf ("UPDATE Branch SET commit_id = %Q "
                           "WHERE name = %Q AND repo_id = %Q",
                           branch->commit_id, branch->name, branch->repo_id);
    sqlite_query_exec (db, sql);
    sqlite3_free (sql);

    pthread_mutex_unlock (&mgr->priv->db_lock);

    return 0;
#else
    int rc = seaf_db_statement_query (mgr->seaf->db,
                                      "UPDATE Branch SET commit_id = ? "
                                      "WHERE name = ? AND repo_id = ?",
                                      3, "string", branch->commit_id,
                                      "string", branch->name,
                                      "string", branch->repo_id);
    if (rc < 0)
        return -1;
    return 0;
#endif
}