#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opt ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_15__ {int /*<<< orphan*/  commit_mgr; int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_14__ {struct TYPE_14__* data; int /*<<< orphan*/  dir_cb; int /*<<< orphan*/  file_cb; int /*<<< orphan*/  version; int /*<<< orphan*/  store_id; int /*<<< orphan*/  fold_dir_diff; int /*<<< orphan*/ ** results; } ;
struct TYPE_13__ {char* root_id; int /*<<< orphan*/ * second_parent_id; int /*<<< orphan*/ * parent_id; int /*<<< orphan*/  repo_id; } ;
struct TYPE_12__ {int /*<<< orphan*/  version; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ SeafRepo ;
typedef  TYPE_2__ SeafCommit ;
typedef  int /*<<< orphan*/  GList ;
typedef  TYPE_3__ DiffOptions ;
typedef  TYPE_3__ DiffData ;

/* Variables and functions */
 int /*<<< orphan*/  diff_resolve_renames (int /*<<< orphan*/ **) ; 
 int diff_trees (int,char const**,TYPE_3__*) ; 
 int /*<<< orphan*/  g_return_val_if_fail (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_8__* seaf ; 
 TYPE_2__* seaf_commit_manager_get_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_commit_unref (TYPE_2__*) ; 
 TYPE_1__* seaf_repo_manager_get_repo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  threeway_diff_dirs ; 
 int /*<<< orphan*/  threeway_diff_files ; 

int
diff_merge (SeafCommit *merge, GList **results, gboolean fold_dir_diff)
{
    SeafRepo *repo = NULL;
    DiffOptions opt;
    const char *roots[3];
    SeafCommit *parent1, *parent2;

    g_return_val_if_fail (*results == NULL, -1);
    g_return_val_if_fail (merge->parent_id != NULL &&
                          merge->second_parent_id != NULL,
                          -1);

    repo = seaf_repo_manager_get_repo (seaf->repo_mgr, merge->repo_id);
    if (!repo) {
        seaf_warning ("Failed to get repo %s.\n", merge->repo_id);
        return -1;
    }

    parent1 = seaf_commit_manager_get_commit (seaf->commit_mgr,
                                              repo->id,
                                              repo->version,
                                              merge->parent_id);
    if (!parent1) {
        seaf_warning ("failed to find commit %s:%s.\n", repo->id, merge->parent_id);
        return -1;
    }

    parent2 = seaf_commit_manager_get_commit (seaf->commit_mgr,
                                              repo->id,
                                              repo->version,
                                              merge->second_parent_id);
    if (!parent2) {
        seaf_warning ("failed to find commit %s:%s.\n",
                      repo->id, merge->second_parent_id);
        seaf_commit_unref (parent1);
        return -1;
    }

    DiffData data;
    memset (&data, 0, sizeof(data));
    data.results = results;
    data.fold_dir_diff = fold_dir_diff;

    memset (&opt, 0, sizeof(opt));
    memcpy (opt.store_id, repo->id, 36);
    opt.version = repo->version;
    opt.file_cb = threeway_diff_files;
    opt.dir_cb = threeway_diff_dirs;
    opt.data = &data;

    roots[0] = merge->root_id;
    roots[1] = parent1->root_id;
    roots[2] = parent2->root_id;

    int ret = diff_trees (3, roots, &opt);
    diff_resolve_renames (results);

    seaf_commit_unref (parent1);
    seaf_commit_unref (parent2);

    return ret;
}