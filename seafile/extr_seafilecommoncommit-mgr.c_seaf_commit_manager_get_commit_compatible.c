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
typedef  int /*<<< orphan*/  SeafCommitManager ;
typedef  int /*<<< orphan*/  SeafCommit ;

/* Variables and functions */
 int /*<<< orphan*/ * seaf_commit_manager_get_commit (int /*<<< orphan*/ *,char const*,int,char const*) ; 

SeafCommit *
seaf_commit_manager_get_commit_compatible (SeafCommitManager *mgr,
                                           const char *repo_id,
                                           const char *id)
{
    SeafCommit *commit = NULL;

    /* First try version 1 layout. */
    commit = seaf_commit_manager_get_commit (mgr, repo_id, 1, id);
    if (commit)
        return commit;

#if defined MIGRATION || defined SEAFILE_CLIENT
    /* For compatibility with version 0. */
    commit = seaf_commit_manager_get_commit (mgr, repo_id, 0, id);
#endif
    return commit;
}