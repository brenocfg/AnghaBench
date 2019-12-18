#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SeafCloneManager ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 char* g_build_filename (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* make_worktree (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

char *
seaf_clone_manager_gen_default_worktree (SeafCloneManager *mgr,
                                         const char *worktree_parent,
                                         const char *repo_name)
{
    char *wt = g_build_filename (worktree_parent, repo_name, NULL);
    char *worktree;

    worktree = make_worktree (mgr, wt, TRUE, NULL);
    if (!worktree)
        return wt;

    g_free (wt);
    return worktree;
}