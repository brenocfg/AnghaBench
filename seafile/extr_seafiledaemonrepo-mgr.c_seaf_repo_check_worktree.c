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
struct TYPE_6__ {int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/ * worktree; } ;
struct TYPE_5__ {int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_1__ SeafStat ;
typedef  TYPE_2__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ g_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ seaf_stat (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

int
seaf_repo_check_worktree (SeafRepo *repo)
{
    SeafStat st;

    if (repo->worktree == NULL) {
        seaf_warning ("Worktree for repo '%s'(%.8s) is not set.\n",
                      repo->name, repo->id);
        return -1;
    }

    /* check repo worktree */
    if (g_access(repo->worktree, F_OK) < 0) {
        seaf_warning ("Failed to access worktree %s for repo '%s'(%.8s)\n",
                      repo->worktree, repo->name, repo->id);
        return -1;
    }
    if (seaf_stat(repo->worktree, &st) < 0) {
        seaf_warning ("Failed to stat worktree %s for repo '%s'(%.8s)\n",
                      repo->worktree, repo->name, repo->id);
        return -1;
    }
    if (!S_ISDIR(st.st_mode)) {
        seaf_warning ("Worktree %s for repo '%s'(%.8s) is not a directory.\n",
                      repo->worktree, repo->name, repo->id);
        return -1;
    }

    return 0;
}