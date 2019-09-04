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
struct TYPE_5__ {int /*<<< orphan*/  branch_mgr; } ;
struct TYPE_4__ {int /*<<< orphan*/  head; int /*<<< orphan*/  repo_id; } ;
typedef  int /*<<< orphan*/  SeafBranch ;
typedef  TYPE_1__ HttpTxTask ;

/* Variables and functions */
 TYPE_3__* seaf ; 
 int /*<<< orphan*/  seaf_branch_manager_add_branch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * seaf_branch_manager_get_branch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seaf_branch_manager_update_branch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * seaf_branch_new (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_branch_set_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_branch_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
update_master_branch (HttpTxTask *task)
{
    SeafBranch *branch;
    branch = seaf_branch_manager_get_branch (seaf->branch_mgr,
                                             task->repo_id,
                                             "master");
    if (!branch) {
        branch = seaf_branch_new ("master", task->repo_id, task->head);
        seaf_branch_manager_add_branch (seaf->branch_mgr, branch);
        seaf_branch_unref (branch);
    } else {
        seaf_branch_set_commit (branch, task->head);
        seaf_branch_manager_update_branch (seaf->branch_mgr, branch);
        seaf_branch_unref (branch);
    }
}