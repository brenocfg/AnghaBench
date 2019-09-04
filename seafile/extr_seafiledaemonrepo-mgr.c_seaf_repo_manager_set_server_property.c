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
typedef  TYPE_2__ SeafRepoManager ;

/* Variables and functions */
 char* canonical_server_url (char const*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char*,char const*,char const*) ; 
 int sqlite_query_exec (int /*<<< orphan*/ ,char*) ; 

int
seaf_repo_manager_set_server_property (SeafRepoManager *mgr,
                                       const char *server_url,
                                       const char *key,
                                       const char *value)
{
    char *sql;
    int ret;
    char *canon_server_url = canonical_server_url(server_url);

    pthread_mutex_lock (&mgr->priv->db_lock);

    sql = sqlite3_mprintf ("REPLACE INTO ServerProperty VALUES (%Q, %Q, %Q);",
                           canon_server_url, key, value);
    ret = sqlite_query_exec (mgr->priv->db, sql);

    pthread_mutex_unlock (&mgr->priv->db_lock);

    sqlite3_free (sql);
    g_free (canon_server_url);
    return ret;
}