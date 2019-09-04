#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opt ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_14__ {int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_13__ {struct TYPE_13__* data; int /*<<< orphan*/  dir_cb; int /*<<< orphan*/  file_cb; int /*<<< orphan*/  version; int /*<<< orphan*/  store_id; int /*<<< orphan*/  fold_dir_diff; int /*<<< orphan*/ ** results; } ;
struct TYPE_12__ {char* root_id; int /*<<< orphan*/  repo_id; } ;
struct TYPE_11__ {int /*<<< orphan*/  version; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ SeafRepo ;
typedef  TYPE_2__ SeafCommit ;
typedef  int /*<<< orphan*/  GList ;
typedef  TYPE_3__ DiffOptions ;
typedef  TYPE_3__ DiffData ;

/* Variables and functions */
 int /*<<< orphan*/  diff_resolve_renames (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  diff_trees (int,char const**,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_6__* seaf ; 
 TYPE_1__* seaf_repo_manager_get_repo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twoway_diff_dirs ; 
 int /*<<< orphan*/  twoway_diff_files ; 

int
diff_commits (SeafCommit *commit1, SeafCommit *commit2, GList **results,
              gboolean fold_dir_diff)
{
    SeafRepo *repo = NULL;
    DiffOptions opt;
    const char *roots[2];

    repo = seaf_repo_manager_get_repo (seaf->repo_mgr, commit1->repo_id);
    if (!repo) {
        seaf_warning ("Failed to get repo %s.\n", commit1->repo_id);
        return -1;
    }

    DiffData data;
    memset (&data, 0, sizeof(data));
    data.results = results;
    data.fold_dir_diff = fold_dir_diff;

    memset (&opt, 0, sizeof(opt));
    memcpy (opt.store_id, repo->id, 36);
    opt.version = repo->version;
    opt.file_cb = twoway_diff_files;
    opt.dir_cb = twoway_diff_dirs;
    opt.data = &data;

    roots[0] = commit1->root_id;
    roots[1] = commit2->root_id;

    diff_trees (2, roots, &opt);
    diff_resolve_renames (results);

    return 0;
}