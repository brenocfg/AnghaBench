#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  sql ;
struct TYPE_9__ {char* id; } ;
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {int /*<<< orphan*/  db_lock; int /*<<< orphan*/ * db; } ;
typedef  TYPE_2__ SeafRepoManager ;
typedef  TYPE_3__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  load_keys_cb ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int sqlite_foreach_selected_row (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int
load_repo_passwd (SeafRepoManager *manager, SeafRepo *repo)
{
    sqlite3 *db = manager->priv->db;
    char sql[256];
    int n;

    pthread_mutex_lock (&manager->priv->db_lock);

    snprintf (sql, sizeof(sql), 
              "SELECT key, iv FROM RepoKeys WHERE repo_id='%s'",
              repo->id);
    n = sqlite_foreach_selected_row (db, sql, load_keys_cb, repo);
    if (n < 0) {
        pthread_mutex_unlock (&manager->priv->db_lock);
        return -1;
    }

    pthread_mutex_unlock (&manager->priv->db_lock);

    return 0;
    
}