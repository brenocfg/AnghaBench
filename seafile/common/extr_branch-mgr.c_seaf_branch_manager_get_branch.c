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
typedef  int /*<<< orphan*/  SeafBranchManager ;
typedef  int /*<<< orphan*/  SeafBranch ;

/* Variables and functions */
 int /*<<< orphan*/ * real_get_branch (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

SeafBranch *
seaf_branch_manager_get_branch (SeafBranchManager *mgr,
                                const char *repo_id,
                                const char *name)
{
    SeafBranch *branch;

    /* "fetch_head" maps to "local" or "master" on client (LAN sync) */
    if (strcmp (name, "fetch_head") == 0) {
        branch = real_get_branch (mgr, repo_id, "local");
        if (!branch) {
            branch = real_get_branch (mgr, repo_id, "master");
        }
        return branch;
    } else {
        return real_get_branch (mgr, repo_id, name);
    }
}