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
typedef  char* gpointer ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  WatchCommand ;
struct TYPE_6__ {int* cmd_pipe; TYPE_1__* priv; } ;
struct TYPE_5__ {int maxfd; int /*<<< orphan*/  handle_hash; int /*<<< orphan*/  read_fds; } ;
typedef  TYPE_1__ SeafWTMonitorPriv ;
typedef  TYPE_2__ SeafWTMonitor ;
typedef  int /*<<< orphan*/  GHashTableIter ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,char**,char**) ; 
 int /*<<< orphan*/  handle_watch_command (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_events (TYPE_1__*,char*,int) ; 
 int seaf_pipe_readn (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static void *
wt_monitor_job_linux (void *vmonitor)
{
    SeafWTMonitor *monitor = vmonitor;
    SeafWTMonitorPriv *priv = monitor->priv;

    WatchCommand cmd;
    int n;
    int rc;
    fd_set fds;
    int inotify_fd;
    char *repo_id;
    gpointer key, value;
    GHashTableIter iter;

    FD_SET (monitor->cmd_pipe[0], &priv->read_fds);
    priv->maxfd = monitor->cmd_pipe[0];

    while (1) {
        fds = priv->read_fds;

        rc = select (priv->maxfd + 1, &fds, NULL, NULL, NULL);
        if (rc < 0 && errno == EINTR) {
            continue;
        } else if (rc < 0) {
            seaf_warning ("[wt mon] select error: %s.\n", strerror(errno));
            break;
        }

        if (FD_ISSET (monitor->cmd_pipe[0], &fds)) {
            n = seaf_pipe_readn (monitor->cmd_pipe[0], &cmd, sizeof(cmd));
            if (n != sizeof(cmd)) {
                seaf_warning ("[wt mon] failed to read command.\n");
                continue;
            }
            handle_watch_command (monitor, &cmd);
        }

        g_hash_table_iter_init (&iter, priv->handle_hash);
        while (g_hash_table_iter_next (&iter, &key, &value)) {
            repo_id = key;
            inotify_fd = (int)(long)value;
            if (FD_ISSET (inotify_fd, &fds))
                process_events (priv, repo_id, inotify_fd);
        }
    }

    return NULL;
}