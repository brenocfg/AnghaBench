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
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ g_access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (char const*) ; 
 int /*<<< orphan*/  seaf_clone_manager_check_worktree_path (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 char* try_worktree (char const*) ; 

__attribute__((used)) static char *
make_worktree_for_download (SeafCloneManager *mgr,
                            const char *wt_tmp,
                            GError **error)
{
    char *worktree;

    if (g_access (wt_tmp, F_OK) == 0) {
        worktree = try_worktree (wt_tmp);
    } else {
        worktree = g_strdup(wt_tmp);
    }

    if (!seaf_clone_manager_check_worktree_path (mgr, worktree, error)) {
        g_free (worktree);
        return NULL;
    }

    return worktree;
}