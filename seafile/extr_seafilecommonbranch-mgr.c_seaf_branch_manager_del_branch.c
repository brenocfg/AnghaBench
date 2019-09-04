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
struct TYPE_4__ {int /*<<< orphan*/  db_lock; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ SeafBranchManager ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,char const*) ; 
 scalar_t__ sqlite_query_exec (int /*<<< orphan*/ ,char*) ; 

int
seaf_branch_manager_del_branch (SeafBranchManager *mgr,
                                const char *repo_id,
                                const char *name)
{
#ifndef SEAFILE_SERVER
    char *sql;

    pthread_mutex_lock (&mgr->priv->db_lock);

    sql = sqlite3_mprintf ("DELETE FROM Branch WHERE name = %Q AND "
                           "repo_id = '%s'", name, repo_id);
    if (sqlite_query_exec (mgr->priv->db, sql) < 0)
        seaf_warning ("Delete branch %s failed\n", name);
    sqlite3_free (sql);

    pthread_mutex_unlock (&mgr->priv->db_lock);

    return 0;
#else
    int rc = seaf_db_statement_query (mgr->seaf->db,
                                      "DELETE FROM Branch WHERE name=? AND repo_id=?",
                                      2, "string", name, "string", repo_id);
    if (rc < 0)
        return -1;
    return 0;
#endif
}