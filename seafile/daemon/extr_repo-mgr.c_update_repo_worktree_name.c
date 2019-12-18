#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gboolean ;
struct TYPE_6__ {int /*<<< orphan*/  wt_monitor; int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/  worktree; } ;
typedef  TYPE_1__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 char* g_build_filename (char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_path_get_basename (int /*<<< orphan*/ ) ; 
 char* g_path_get_dirname (int /*<<< orphan*/ ) ; 
 scalar_t__ g_strcmp0 (char*,char*) ; 
 TYPE_4__* seaf ; 
 int /*<<< orphan*/  seaf_message (char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ seaf_repo_manager_set_repo_worktree (int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 scalar_t__ seaf_util_rename (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ seaf_wt_monitor_unwatch_repo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ seaf_wt_monitor_watch_repo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_repo_worktree_name (SeafRepo *repo, const char *new_name, gboolean rewatch)
{
    char *dirname = NULL, *basename = NULL;
    char *new_worktree = NULL;

    seaf_message ("Update worktree folder name of repo %s to %s.\n",
                  repo->id, new_name);

    dirname = g_path_get_dirname (repo->worktree);
    if (g_strcmp0 (dirname, ".") == 0)
        return;
    basename = g_path_get_basename (repo->worktree);

    new_worktree = g_build_filename (dirname, new_name, NULL);

    /* This can possibly fail on Windows if some files are opened under the worktree.
     * The rename operation will be retried on next restart.
     */
    if (seaf_util_rename (repo->worktree, new_worktree) < 0) {
        seaf_warning ("Failed to rename worktree from %s to %s: %s.\n",
                      repo->worktree, new_worktree, strerror(errno));
        goto out;
    }

    if (seaf_repo_manager_set_repo_worktree (seaf->repo_mgr, repo, new_worktree) < 0) {
        goto out;
    }

    if (rewatch) {
        if (seaf_wt_monitor_unwatch_repo (seaf->wt_monitor, repo->id) < 0) {
            seaf_warning ("Failed to unwatch repo %s old worktree.\n", repo->id);
            goto out;
        }

        if (seaf_wt_monitor_watch_repo (seaf->wt_monitor, repo->id, repo->worktree) < 0) {
            seaf_warning ("Failed to watch repo %s new worktree.\n", repo->id);
        }
    }

out:
    g_free (dirname);
    g_free (basename);
    g_free (new_worktree);
}