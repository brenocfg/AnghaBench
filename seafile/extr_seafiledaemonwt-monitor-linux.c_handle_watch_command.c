#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gpointer ;
struct TYPE_10__ {scalar_t__ type; int /*<<< orphan*/  repo_id; int /*<<< orphan*/  worktree; } ;
typedef  TYPE_1__ WatchCommand ;
struct TYPE_12__ {TYPE_2__* priv; } ;
struct TYPE_11__ {int /*<<< orphan*/  handle_hash; } ;
typedef  TYPE_2__ SeafWTMonitorPriv ;
typedef  TYPE_3__ SeafWTMonitor ;

/* Variables and functions */
 scalar_t__ CMD_ADD_WATCH ; 
 scalar_t__ CMD_DELETE_WATCH ; 
 scalar_t__ CMD_REFRESH_WATCH ; 
 scalar_t__ g_hash_table_lookup_extended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ handle_add_repo (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ handle_refresh_repo (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_rm_repo (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reply_watch_command (TYPE_3__*,int) ; 
 int /*<<< orphan*/  seaf_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_watch_command (SeafWTMonitor *monitor, WatchCommand *cmd)
{
    SeafWTMonitorPriv *priv = monitor->priv;

    if (cmd->type == CMD_ADD_WATCH) {
        if (g_hash_table_lookup_extended (priv->handle_hash, cmd->repo_id,
                                          NULL, NULL)) {
            reply_watch_command (monitor, 0);
            return;
        }

        if (handle_add_repo(priv, cmd->repo_id, cmd->worktree) < 0) {
            seaf_warning ("[wt mon] failed to watch worktree of repo %s.\n",
                          cmd->repo_id);
            reply_watch_command (monitor, -1);
            return;
        }

        seaf_debug ("[wt mon] add watch for repo %s\n", cmd->repo_id);
        reply_watch_command (monitor, 0);
    } else if (cmd->type == CMD_DELETE_WATCH) {
        gpointer key, value;
        if (!g_hash_table_lookup_extended (priv->handle_hash, cmd->repo_id,
                                           &key, &value)) {
            reply_watch_command (monitor, 0);
            return;
        }

        handle_rm_repo (monitor, cmd->repo_id, value);
        reply_watch_command (monitor, 0);
    } else if (cmd->type ==  CMD_REFRESH_WATCH) {
        if (handle_refresh_repo (priv, cmd->repo_id) < 0) {
            seaf_warning ("[wt mon] failed to refresh watch of repo %s.\n",
                          cmd->repo_id);
            reply_watch_command (monitor, -1);
            return;
        }
        reply_watch_command (monitor, 0);
    }
}