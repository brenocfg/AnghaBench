#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opts ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_21__ {TYPE_4__* block_list; int /*<<< orphan*/  added_blocks; struct TYPE_21__* data; int /*<<< orphan*/  dir_cb; int /*<<< orphan*/  file_cb; int /*<<< orphan*/  version; int /*<<< orphan*/  store_id; TYPE_3__* task; } ;
struct TYPE_20__ {int /*<<< orphan*/  data; struct TYPE_20__* next; } ;
struct TYPE_19__ {int /*<<< orphan*/  repo_id; int /*<<< orphan*/  repo_version; } ;
struct TYPE_18__ {int /*<<< orphan*/  commit_id; } ;
struct TYPE_17__ {char* root_id; } ;
struct TYPE_16__ {int /*<<< orphan*/  commit_mgr; int /*<<< orphan*/  branch_mgr; } ;
typedef  TYPE_1__ SeafCommit ;
typedef  TYPE_2__ SeafBranch ;
typedef  TYPE_3__ HttpTxTask ;
typedef  TYPE_4__ GList ;
typedef  TYPE_5__ DiffOptions ;
typedef  TYPE_5__ CalcBlockListData ;

/* Variables and functions */
 int /*<<< orphan*/  block_list_diff_dirs ; 
 int /*<<< orphan*/  block_list_diff_files ; 
 scalar_t__ diff_trees (int,char const**,TYPE_5__*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_hash_table_new_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_str_equal ; 
 int /*<<< orphan*/  g_str_hash ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 TYPE_11__* seaf ; 
 TYPE_2__* seaf_branch_manager_get_branch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seaf_branch_unref (TYPE_2__*) ; 
 TYPE_1__* seaf_commit_manager_get_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_commit_unref (TYPE_1__*) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
calculate_block_list (HttpTxTask *task, GList **plist)
{
    int ret = 0;
    SeafBranch *local = NULL, *master = NULL;
    SeafCommit *local_head = NULL, *master_head = NULL;

    local = seaf_branch_manager_get_branch (seaf->branch_mgr, task->repo_id, "local");
    if (!local) {
        seaf_warning ("Branch local not found for repo %.8s.\n", task->repo_id);
        ret = -1;
        goto out;
    }
    master = seaf_branch_manager_get_branch (seaf->branch_mgr, task->repo_id, "master");
    if (!master) {
        seaf_warning ("Branch master not found for repo %.8s.\n", task->repo_id);
        ret = -1;
        goto out;
    }

    local_head = seaf_commit_manager_get_commit (seaf->commit_mgr,
                                                 task->repo_id, task->repo_version,
                                                 local->commit_id);
    if (!local_head) {
        seaf_warning ("Local head commit not found for repo %.8s.\n",
                      task->repo_id);
        ret = -1;
        goto out;
    }
    master_head = seaf_commit_manager_get_commit (seaf->commit_mgr,
                                                 task->repo_id, task->repo_version,
                                                 master->commit_id);
    if (!master_head) {
        seaf_warning ("Master head commit not found for repo %.8s.\n",
                      task->repo_id);
        ret = -1;
        goto out;
    }

    CalcBlockListData data;
    memset (&data, 0, sizeof(data));
    data.added_blocks = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);
    data.task = task;

    DiffOptions opts;
    memset (&opts, 0, sizeof(opts));
    memcpy (opts.store_id, task->repo_id, 36);
    opts.version = task->repo_version;
    opts.file_cb = block_list_diff_files;
    opts.dir_cb = block_list_diff_dirs;
    opts.data = &data;

    const char *trees[2];
    trees[0] = local_head->root_id;
    trees[1] = master_head->root_id;
    if (diff_trees (2, trees, &opts) < 0) {
        seaf_warning ("Failed to diff local and master head for repo %.8s.\n",
                      task->repo_id);
        g_hash_table_destroy (data.added_blocks);

        GList *ptr;
        for (ptr = data.block_list; ptr; ptr = ptr->next)
            g_free (ptr->data);

        ret = -1;
        goto out;
    }

    g_hash_table_destroy (data.added_blocks);
    *plist = data.block_list;

out:
    seaf_branch_unref (local);
    seaf_branch_unref (master);
    seaf_commit_unref (local_head);
    seaf_commit_unref (master_head);
    return ret;
}