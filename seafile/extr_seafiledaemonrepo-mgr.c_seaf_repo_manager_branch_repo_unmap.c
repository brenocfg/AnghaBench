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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_8__ {int /*<<< orphan*/  repo_id; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  db_lock; int /*<<< orphan*/ * db; } ;
typedef  TYPE_2__ SeafRepoManager ;
typedef  TYPE_3__ SeafBranch ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite_query_exec (int /*<<< orphan*/ *,char*) ; 

int
seaf_repo_manager_branch_repo_unmap (SeafRepoManager *manager, SeafBranch *branch)
{
    char *sql;
    sqlite3 *db = manager->priv->db;

    pthread_mutex_lock (&manager->priv->db_lock);

    sql = sqlite3_mprintf ("DELETE FROM RepoBranch WHERE branch_name = %Q"
                           " AND repo_id = %Q",
                           branch->name, branch->repo_id);
    if (sqlite_query_exec (db, sql) < 0) {
        seaf_warning ("Unmap branch repo failed\n");
        pthread_mutex_unlock (&manager->priv->db_lock);
        sqlite3_free (sql);
        return -1;
    }

    sqlite3_free (sql);
    pthread_mutex_unlock (&manager->priv->db_lock);

    return 0;
}