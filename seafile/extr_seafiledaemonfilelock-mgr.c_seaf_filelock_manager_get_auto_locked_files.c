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
typedef  TYPE_2__ SeafFilelockManager ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 int /*<<< orphan*/  _LOCKED_AUTO ; 
 int /*<<< orphan*/  collect_auto_locked_files ; 
 int /*<<< orphan*/ * g_list_reverse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite_foreach_selected_row (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

GList *
seaf_filelock_manager_get_auto_locked_files (SeafFilelockManager *mgr)
{
    char *sql;
    GList *ret = NULL;

    pthread_mutex_lock (&mgr->priv->db_lock);

    sql = sqlite3_mprintf ("SELECT repo_id, path FROM ServerLockedFiles "
                           "WHERE locked_by_me = %d", _LOCKED_AUTO);
    sqlite_foreach_selected_row (mgr->priv->db, sql,
                                 collect_auto_locked_files,
                                 &ret);

    pthread_mutex_unlock (&mgr->priv->db_lock);

    ret = g_list_reverse (ret);

    sqlite3_free (sql);
    return ret;
}