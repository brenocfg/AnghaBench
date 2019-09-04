#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  version; int /*<<< orphan*/  repo_id; } ;
typedef  int /*<<< orphan*/  SeafCommitManager ;
typedef  TYPE_1__ SeafCommit ;

/* Variables and functions */
 int save_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

int
seaf_commit_manager_add_commit (SeafCommitManager *mgr,
                                SeafCommit *commit)
{
    int ret;

    /* add_commit_to_cache (mgr, commit); */
    if ((ret = save_commit (mgr, commit->repo_id, commit->version, commit)) < 0)
        return -1;
    
    return 0;
}