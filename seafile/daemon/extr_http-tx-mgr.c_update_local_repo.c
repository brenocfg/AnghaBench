#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
struct TYPE_17__ {void* error; int /*<<< orphan*/  repo_id; int /*<<< orphan*/  head; scalar_t__ is_clone; int /*<<< orphan*/  repo_version; } ;
struct TYPE_16__ {int /*<<< orphan*/  repo_name; int /*<<< orphan*/  commit_id; int /*<<< orphan*/  repo_id; } ;
struct TYPE_15__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * head; } ;
struct TYPE_14__ {int /*<<< orphan*/  branch_mgr; int /*<<< orphan*/  repo_mgr; int /*<<< orphan*/  commit_mgr; } ;
typedef  TYPE_1__ SeafRepo ;
typedef  TYPE_2__ SeafCommit ;
typedef  int /*<<< orphan*/  SeafBranch ;
typedef  TYPE_3__ HttpTxTask ;

/* Variables and functions */
 void* SYNC_ERROR_ID_LOCAL_DATA_CORRUPT ; 
 void* SYNC_ERROR_ID_NOT_ENOUGH_MEMORY ; 
 scalar_t__ g_strcmp0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_13__* seaf ; 
 int /*<<< orphan*/  seaf_branch_manager_add_branch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * seaf_branch_manager_get_branch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seaf_branch_manager_update_branch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * seaf_branch_new (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_branch_set_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_branch_unref (int /*<<< orphan*/ *) ; 
 TYPE_2__* seaf_commit_manager_get_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_commit_unref (TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_repo_from_commit (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_repo_manager_add_repo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* seaf_repo_manager_get_repo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* seaf_repo_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_repo_set_name (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
update_local_repo (HttpTxTask *task)
{
    SeafRepo *repo;
    SeafCommit *new_head;
    SeafBranch *branch;
    int ret = 0;

    new_head = seaf_commit_manager_get_commit (seaf->commit_mgr,
                                               task->repo_id,
                                               task->repo_version,
                                               task->head);
    if (!new_head) {
        seaf_warning ("Failed to get commit %s:%s.\n", task->repo_id, task->head);
        task->error = SYNC_ERROR_ID_LOCAL_DATA_CORRUPT;
        return -1;
    }

    /* If repo doesn't exist, create it.
     * Note that branch doesn't exist either in this case.
     */
    repo = seaf_repo_manager_get_repo (seaf->repo_mgr, new_head->repo_id);
    if (task->is_clone) {
        if (repo != NULL)
            goto out;

        repo = seaf_repo_new (new_head->repo_id, NULL, NULL);
        if (repo == NULL) {
            /* create repo failed */
            task->error = SYNC_ERROR_ID_NOT_ENOUGH_MEMORY;
            ret = -1;
            goto out;
        }

        seaf_repo_from_commit (repo, new_head);

        seaf_repo_manager_add_repo (seaf->repo_mgr, repo);

        /* If it's a new repo, create 'local' and 'master' branch */
        branch = seaf_branch_new ("local", task->repo_id, task->head);
        seaf_branch_manager_add_branch (seaf->branch_mgr, branch);
        seaf_branch_unref (branch);

        branch = seaf_branch_new ("master", task->repo_id, task->head);
        seaf_branch_manager_add_branch (seaf->branch_mgr, branch);
        seaf_branch_unref (branch);
    } else {
        if (!repo) {
            task->error = SYNC_ERROR_ID_LOCAL_DATA_CORRUPT;
            ret = -1;
            goto out;
        }

        branch = seaf_branch_manager_get_branch (seaf->branch_mgr, 
                                                 task->repo_id,
                                                 "master");
        if (!branch) {
            seaf_warning ("Branch master not found for repo %.8s.\n", task->repo_id);
            task->error = SYNC_ERROR_ID_LOCAL_DATA_CORRUPT;
            ret = -1;
            goto out;
        }
        seaf_branch_set_commit (branch, new_head->commit_id);
        seaf_branch_manager_update_branch (seaf->branch_mgr, branch);
        seaf_branch_unref (branch);

        /* Update repo head branch. */
        seaf_branch_set_commit (repo->head, new_head->commit_id);
        seaf_branch_manager_update_branch (seaf->branch_mgr, repo->head);

        if (g_strcmp0 (repo->name, new_head->repo_name) != 0)
            seaf_repo_set_name (repo, new_head->repo_name);
    }

out:
    seaf_commit_unref (new_head);
    return ret;
}