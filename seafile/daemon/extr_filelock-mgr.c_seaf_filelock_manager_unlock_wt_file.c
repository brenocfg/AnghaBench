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
struct TYPE_5__ {int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_4__ {int /*<<< orphan*/  worktree; } ;
typedef  TYPE_1__ SeafRepo ;
typedef  int /*<<< orphan*/  SeafFilelockManager ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEAF_PATH_PERM_RW ; 
 char* g_build_filename (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 TYPE_3__* seaf ; 
 TYPE_1__* seaf_repo_manager_get_repo (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  seaf_set_path_permission (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_unset_path_permission (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ seaf_util_exists (char*) ; 

void
seaf_filelock_manager_unlock_wt_file (SeafFilelockManager *mgr,
                                      const char *repo_id,
                                      const char *path)
{
    SeafRepo *repo = seaf_repo_manager_get_repo (seaf->repo_mgr, repo_id);
    if (!repo)
        return;

    char *fullpath = g_build_filename (repo->worktree, path, NULL);

#ifdef WIN32
    if (seaf_util_exists (fullpath))
        seaf_unset_path_permission (fullpath, FALSE);
#else
    if (seaf_util_exists (fullpath))
        seaf_set_path_permission (fullpath, SEAF_PATH_PERM_RW, FALSE);
#endif
    g_free (fullpath);
}