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
typedef  scalar_t__ gpointer ;
struct TYPE_5__ {int* cmd_pipe; TYPE_1__* priv; } ;
struct TYPE_4__ {int maxfd; int /*<<< orphan*/  info_hash; } ;
typedef  TYPE_1__ SeafWTMonitorPriv ;
typedef  TYPE_2__ SeafWTMonitor ;
typedef  int /*<<< orphan*/  GHashTableIter ;

/* Variables and functions */
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static void
update_maxfd (SeafWTMonitor *monitor)
{
    SeafWTMonitorPriv *priv = monitor->priv;
    GHashTableIter iter;
    gpointer key, value;
    int fd, maxfd = monitor->cmd_pipe[0];

    g_hash_table_iter_init (&iter, priv->info_hash);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        fd = (int) (long)key;
        if (fd > maxfd)
            maxfd = fd;
    }

    priv->maxfd = maxfd;
}