#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  db_lock; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ SeafRepoManager ;

/* Variables and functions */
 int /*<<< orphan*/  REPO_PROP_SERVER_URL ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 char* seaf_repo_manager_get_repo_property (TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,char*) ; 
 int /*<<< orphan*/  sqlite_query_exec (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
update_server_properties (SeafRepoManager *mgr,
                          const char *repo_id,
                          const char *new_server_url)
{
    char *old_server_url = NULL;
    char *sql = NULL;

    old_server_url = seaf_repo_manager_get_repo_property (mgr, repo_id,
                                                          REPO_PROP_SERVER_URL);
    if (!old_server_url)
        return;

    pthread_mutex_lock (&mgr->priv->db_lock);

    sql = sqlite3_mprintf ("UPDATE ServerProperty SET server_url=%Q WHERE "
                           "server_url=%Q;", new_server_url, old_server_url);
    sqlite_query_exec (mgr->priv->db, sql);

    pthread_mutex_unlock (&mgr->priv->db_lock);

    sqlite3_free (sql);
    g_free (old_server_url);
}