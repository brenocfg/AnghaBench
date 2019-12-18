#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  commit_id; } ;
struct TYPE_13__ {int /*<<< orphan*/  is_corrupted; int /*<<< orphan*/  id; } ;
struct TYPE_12__ {TYPE_1__* seaf; } ;
struct TYPE_11__ {int /*<<< orphan*/  commit_mgr; } ;
typedef  TYPE_2__ SeafRepoManager ;
typedef  TYPE_3__ SeafRepo ;
typedef  int /*<<< orphan*/  SeafCommit ;
typedef  TYPE_4__ SeafBranch ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * seaf_commit_manager_get_commit_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_commit_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_repo_from_commit (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_head_common (TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static void
load_repo_commit (SeafRepoManager *manager,
                  SeafRepo *repo,
                  SeafBranch *branch)
{
    SeafCommit *commit;

    commit = seaf_commit_manager_get_commit_compatible (manager->seaf->commit_mgr,
                                                        repo->id,
                                                        branch->commit_id);
    if (!commit) {
        seaf_warning ("Commit %s is missing\n", branch->commit_id);
        repo->is_corrupted = TRUE;
        return;
    }

    set_head_common (repo, branch);
    seaf_repo_from_commit (repo, commit);

    seaf_commit_unref (commit);
}