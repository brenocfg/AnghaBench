#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  sql ;
struct TYPE_10__ {char* id; TYPE_2__* manager; } ;
struct TYPE_9__ {TYPE_1__* priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  repo_hash; int /*<<< orphan*/  db_lock; int /*<<< orphan*/ * db; } ;
typedef  TYPE_2__ SeafRepoManager ;
typedef  TYPE_3__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  g_strdup (char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_repo_manager_remove_garbage_repo (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  sqlite_query_exec (int /*<<< orphan*/ *,char*) ; 

int
seaf_repo_manager_add_repo (SeafRepoManager *manager,
                            SeafRepo *repo)
{
    char sql[256];
    sqlite3 *db = manager->priv->db;

    pthread_mutex_lock (&manager->priv->db_lock);

    snprintf (sql, sizeof(sql), "REPLACE INTO Repo VALUES ('%s');", repo->id);
    sqlite_query_exec (db, sql);

    pthread_mutex_unlock (&manager->priv->db_lock);

    /* There may be a "deletion record" for this repo when it was deleted
     * last time.
     */
    seaf_repo_manager_remove_garbage_repo (manager, repo->id);

    repo->manager = manager;

    if (pthread_rwlock_wrlock (&manager->priv->lock) < 0) {
        seaf_warning ("[repo mgr] failed to lock repo cache.\n");
        return -1;
    }

    g_hash_table_insert (manager->priv->repo_hash, g_strdup(repo->id), repo);

    pthread_rwlock_unlock (&manager->priv->lock);

    return 0;
}