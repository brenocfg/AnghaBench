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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  WTStatus ;
struct TYPE_8__ {int /*<<< orphan*/ * status; } ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  info_hash; int /*<<< orphan*/  handle_hash; } ;
typedef  TYPE_1__ SeafWTMonitorPriv ;
typedef  TYPE_2__ SeafWTMonitor ;
typedef  TYPE_3__ RepoWatchInfo ;

/* Variables and functions */
 TYPE_3__* g_hash_table_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_hash_table_lookup_extended (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wt_status_ref (int /*<<< orphan*/ *) ; 

WTStatus *
seaf_wt_monitor_get_worktree_status (SeafWTMonitor *monitor,
                                     const char *repo_id)
{
    SeafWTMonitorPriv *priv = monitor->priv;
    gpointer key, value;
    RepoWatchInfo *info;

    pthread_mutex_lock (&priv->hash_lock);

    if (!g_hash_table_lookup_extended (priv->handle_hash, repo_id,
                                       &key, &value)) {
        pthread_mutex_unlock (&priv->hash_lock);
        return NULL;
    }

    info = g_hash_table_lookup(priv->info_hash, value);
    wt_status_ref (info->status);

    pthread_mutex_unlock (&priv->hash_lock);

    return info->status;
}