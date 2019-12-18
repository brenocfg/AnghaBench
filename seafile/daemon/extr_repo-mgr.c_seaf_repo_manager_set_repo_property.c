#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  wt_monitor; int /*<<< orphan*/  started; int /*<<< orphan*/  sync_mgr; } ;
struct TYPE_4__ {int auto_sync; scalar_t__ sync_interval; char* server_url; char* effective_host; int /*<<< orphan*/  is_readonly; int /*<<< orphan*/  worktree; int /*<<< orphan*/  id; scalar_t__ last_sync_time; } ;
typedef  int /*<<< orphan*/  SeafRepoManager ;
typedef  TYPE_1__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  REPO_AUTO_SYNC ; 
 int /*<<< orphan*/  REPO_PROP_IS_READONLY ; 
 int /*<<< orphan*/  REPO_PROP_SERVER_URL ; 
 int /*<<< orphan*/  REPO_PROP_SYNC_INTERVAL ; 
 int /*<<< orphan*/  TRUE ; 
 int atoi (char const*) ; 
 char* canonical_server_url (char const*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_strcmp0 (char const*,char*) ; 
 int /*<<< orphan*/  save_repo_property (int /*<<< orphan*/ *,char const*,char const*,char const*) ; 
 TYPE_3__* seaf ; 
 int /*<<< orphan*/  seaf_message (char*) ; 
 TYPE_1__* seaf_repo_manager_get_repo (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  seaf_sync_manager_cancel_sync_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_sync_manager_remove_active_path_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_wt_monitor_unwatch_repo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_wt_monitor_watch_repo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int
seaf_repo_manager_set_repo_property (SeafRepoManager *manager, 
                                     const char *repo_id,
                                     const char *key,
                                     const char *value)
{
    SeafRepo *repo;

    repo = seaf_repo_manager_get_repo (manager, repo_id);
    if (!repo)
        return -1;

    if (strcmp(key, REPO_AUTO_SYNC) == 0) {
        if (!seaf->started) {
            seaf_message ("System not started, skip setting auto sync value.\n");
            return 0;
        }

        if (g_strcmp0(value, "true") == 0) {
            repo->auto_sync = 1;
            if (repo->sync_interval == 0)
                seaf_wt_monitor_watch_repo (seaf->wt_monitor, repo->id,
                                            repo->worktree);
            repo->last_sync_time = 0;
        } else {
            repo->auto_sync = 0;
            if (repo->sync_interval == 0)
                seaf_wt_monitor_unwatch_repo (seaf->wt_monitor, repo->id);
            /* Cancel current sync task if any. */
            seaf_sync_manager_cancel_sync_task (seaf->sync_mgr, repo->id);
            seaf_sync_manager_remove_active_path_info (seaf->sync_mgr, repo->id);
        }
    }

    if (strcmp(key, REPO_PROP_SYNC_INTERVAL) == 0) {
        if (!seaf->started) {
            seaf_message ("System not started, skip setting auto sync value.\n");
            return 0;
        }

        int interval = atoi(value);

        if (interval > 0) {
            repo->sync_interval = interval;
            if (repo->auto_sync)
                seaf_wt_monitor_unwatch_repo (seaf->wt_monitor, repo->id);
        } else {
            repo->sync_interval = 0;
            if (repo->auto_sync)
                seaf_wt_monitor_watch_repo (seaf->wt_monitor, repo->id,
                                            repo->worktree);
        }
    }

    if (strcmp (key, REPO_PROP_SERVER_URL) == 0) {
        char *url = canonical_server_url (value);

        if (!repo->server_url) {
            /* Called from clone-mgr. */
            repo->server_url = url;
        } else {
            g_free (repo->server_url);
            repo->server_url = url;

            g_free (repo->effective_host);
            repo->effective_host = NULL;
        }

        save_repo_property (manager, repo_id, key, url);
        return 0;
    }

    if (strcmp (key, REPO_PROP_IS_READONLY) == 0) {
       if (g_strcmp0 (value, "true") == 0)
           repo->is_readonly = TRUE;
       else
           repo->is_readonly = FALSE;
    }

    save_repo_property (manager, repo_id, key, value);
    return 0;
}