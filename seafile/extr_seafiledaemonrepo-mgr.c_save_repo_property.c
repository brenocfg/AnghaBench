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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  db_lock; int /*<<< orphan*/ * db; } ;
typedef  TYPE_2__ SeafRepoManager ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,char const*,...) ; 
 scalar_t__ sqlite_check_for_existence (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sqlite_query_exec (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
save_repo_property (SeafRepoManager *manager,
                    const char *repo_id,
                    const char *key, const char *value)
{
    char *sql;
    sqlite3 *db = manager->priv->db;

    pthread_mutex_lock (&manager->priv->db_lock);

    sql = sqlite3_mprintf ("SELECT repo_id FROM RepoProperty WHERE repo_id=%Q AND key=%Q",
                           repo_id, key);
    if (sqlite_check_for_existence(db, sql)) {
        sqlite3_free (sql);
        sql = sqlite3_mprintf ("UPDATE RepoProperty SET value=%Q"
                               "WHERE repo_id=%Q and key=%Q",
                               value, repo_id, key);
        sqlite_query_exec (db, sql);
        sqlite3_free (sql);
    } else {
        sqlite3_free (sql);
        sql = sqlite3_mprintf ("INSERT INTO RepoProperty VALUES (%Q, %Q, %Q)",
                               repo_id, key, value);
        sqlite_query_exec (db, sql);
        sqlite3_free (sql);
    }

    pthread_mutex_unlock (&manager->priv->db_lock);
}