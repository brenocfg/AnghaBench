#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  worktree_invalid; scalar_t__ worktree; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  SeafRepoManager ;
typedef  TYPE_1__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ g_access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (scalar_t__) ; 
 scalar_t__ g_strdup (char const*) ; 
 scalar_t__ seaf_repo_manager_set_repo_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 

int
seaf_repo_manager_set_repo_worktree (SeafRepoManager *mgr,
                                     SeafRepo *repo,
                                     const char *worktree)
{
    if (g_access(worktree, F_OK) != 0)
        return -1;

    if (repo->worktree)
        g_free (repo->worktree);
    repo->worktree = g_strdup(worktree);

    if (seaf_repo_manager_set_repo_property (mgr, repo->id,
                                             "worktree",
                                             repo->worktree) < 0)
        return -1;

    repo->worktree_invalid = FALSE;

    return 0;
}