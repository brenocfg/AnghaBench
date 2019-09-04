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
struct TYPE_5__ {int /*<<< orphan*/  wt_monitor; } ;
struct TYPE_4__ {scalar_t__ sync_interval; int /*<<< orphan*/  id; int /*<<< orphan*/  worktree; scalar_t__ auto_sync; scalar_t__ worktree_invalid; } ;
typedef  int /*<<< orphan*/  SeafRepoManager ;
typedef  TYPE_1__ SeafRepo ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 TYPE_3__* seaf ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ seaf_wt_monitor_watch_repo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
seaf_repo_manager_validate_repo_worktree (SeafRepoManager *mgr,
                                          SeafRepo *repo)
{
    if (!repo->worktree_invalid)
        return;

    repo->worktree_invalid = FALSE;

    if (repo->auto_sync && (repo->sync_interval == 0)) {
        if (seaf_wt_monitor_watch_repo (seaf->wt_monitor, repo->id, repo->worktree) < 0) {
            seaf_warning ("failed to watch repo %s.\n", repo->id);
        }
    }
}