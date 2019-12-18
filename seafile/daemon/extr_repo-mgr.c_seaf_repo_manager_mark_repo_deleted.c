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
struct TYPE_8__ {char* id; int /*<<< orphan*/  delete_pending; } ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  db_lock; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ SeafRepoManager ;
typedef  TYPE_3__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ sqlite_query_exec (int /*<<< orphan*/ ,char*) ; 

int
seaf_repo_manager_mark_repo_deleted (SeafRepoManager *mgr, SeafRepo *repo)
{
    char sql[256];

    pthread_mutex_lock (&mgr->priv->db_lock);

    snprintf (sql, sizeof(sql), "INSERT INTO DeletedRepo VALUES ('%s')",
              repo->id);
    if (sqlite_query_exec (mgr->priv->db, sql) < 0) {
        pthread_mutex_unlock (&mgr->priv->db_lock);
        return -1;
    }

    pthread_mutex_unlock (&mgr->priv->db_lock);

    repo->delete_pending = TRUE;

    return 0;
}