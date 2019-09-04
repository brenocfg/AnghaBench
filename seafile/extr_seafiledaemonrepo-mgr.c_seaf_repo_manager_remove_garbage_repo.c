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
typedef  int /*<<< orphan*/  sql ;
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  db_lock; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ SeafRepoManager ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  sqlite_query_exec (int /*<<< orphan*/ ,char*) ; 

void
seaf_repo_manager_remove_garbage_repo (SeafRepoManager *mgr, const char *repo_id)
{
    char sql[256];

    pthread_mutex_lock (&mgr->priv->db_lock);

    snprintf (sql, sizeof(sql), "DELETE FROM GarbageRepos WHERE repo_id='%s'",
              repo_id);
    sqlite_query_exec (mgr->priv->db, sql);

    pthread_mutex_unlock (&mgr->priv->db_lock);
}