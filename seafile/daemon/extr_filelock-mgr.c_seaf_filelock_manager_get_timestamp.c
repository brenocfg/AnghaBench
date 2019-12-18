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
typedef  int /*<<< orphan*/  gint64 ;
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  db_lock; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ SeafFilelockManager ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,char const*) ; 
 int /*<<< orphan*/  sqlite_get_int64 (int /*<<< orphan*/ ,char*) ; 

gint64
seaf_filelock_manager_get_timestamp (SeafFilelockManager *mgr,
                                     const char *repo_id)
{
    char sql[256];
    gint64 ret;

    sqlite3_snprintf (sizeof(sql), sql,
                      "SELECT timestamp FROM ServerLockedFilesTimestamp WHERE repo_id = '%q'",
                      repo_id);

    pthread_mutex_lock (&mgr->priv->db_lock);

    ret = sqlite_get_int64 (mgr->priv->db, sql);

    pthread_mutex_unlock (&mgr->priv->db_lock);

    return ret;
}