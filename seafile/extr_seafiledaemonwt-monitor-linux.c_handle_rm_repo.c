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
typedef  char const* gpointer ;
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  info_hash; int /*<<< orphan*/  handle_hash; int /*<<< orphan*/  read_fds; } ;
typedef  TYPE_1__ SeafWTMonitorPriv ;
typedef  TYPE_2__ SeafWTMonitor ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLR (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  g_hash_table_remove (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_maxfd (TYPE_2__*) ; 

__attribute__((used)) static int handle_rm_repo (SeafWTMonitor *monitor,
                           const char *repo_id,
                           gpointer handle)
{
    SeafWTMonitorPriv *priv = monitor->priv;
    int inotify_fd = (int)(long)handle;

    close (inotify_fd);
    FD_CLR (inotify_fd, &priv->read_fds);
    update_maxfd (monitor);

    pthread_mutex_lock (&priv->hash_lock);
    g_hash_table_remove (priv->handle_hash, repo_id);
    g_hash_table_remove (priv->info_hash, (gpointer)(long)inotify_fd);
    pthread_mutex_unlock (&priv->hash_lock);

    return 0;
}