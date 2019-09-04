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
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  db_lock; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ SeafBranchManager ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  sqlite_check_for_existence (int /*<<< orphan*/ ,char*) ; 

gboolean
seaf_branch_manager_branch_exists (SeafBranchManager *mgr,
                                   const char *repo_id,
                                   const char *name)
{
#ifndef SEAFILE_SERVER
    char *sql;
    gboolean ret;

    pthread_mutex_lock (&mgr->priv->db_lock);

    sql = sqlite3_mprintf ("SELECT name FROM Branch WHERE name = %Q "
                           "AND repo_id='%s'", name, repo_id);
    ret = sqlite_check_for_existence (mgr->priv->db, sql);
    sqlite3_free (sql);

    pthread_mutex_unlock (&mgr->priv->db_lock);
    return ret;
#else
    gboolean db_err = FALSE;

    return seaf_db_statement_exists (mgr->seaf->db,
                                     "SELECT name FROM Branch WHERE name=? "
                                     "AND repo_id=?", &db_err,
                                     2, "string", name, "string", repo_id);
#endif
}