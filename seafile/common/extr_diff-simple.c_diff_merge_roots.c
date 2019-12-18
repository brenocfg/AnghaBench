#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opt ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_5__ {int version; struct TYPE_5__* data; int /*<<< orphan*/  dir_cb; int /*<<< orphan*/  file_cb; int /*<<< orphan*/  store_id; int /*<<< orphan*/  fold_dir_diff; int /*<<< orphan*/ ** results; } ;
typedef  int /*<<< orphan*/  GList ;
typedef  TYPE_1__ DiffOptions ;
typedef  TYPE_1__ DiffData ;

/* Variables and functions */
 int /*<<< orphan*/  diff_resolve_renames (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  diff_trees (int,char const**,TYPE_1__*) ; 
 int /*<<< orphan*/  g_return_val_if_fail (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  threeway_diff_dirs ; 
 int /*<<< orphan*/  threeway_diff_files ; 

int
diff_merge_roots (const char *store_id, int version,
                  const char *merged_root, const char *p1_root, const char *p2_root,
                  GList **results, gboolean fold_dir_diff)
{
    DiffOptions opt;
    const char *roots[3];

    g_return_val_if_fail (*results == NULL, -1);

    DiffData data;
    memset (&data, 0, sizeof(data));
    data.results = results;
    data.fold_dir_diff = fold_dir_diff;

    memset (&opt, 0, sizeof(opt));
    memcpy (opt.store_id, store_id, 36);
    opt.version = version;
    opt.file_cb = threeway_diff_files;
    opt.dir_cb = threeway_diff_dirs;
    opt.data = &data;

    roots[0] = merged_root;
    roots[1] = p1_root;
    roots[2] = p2_root;

    diff_trees (3, roots, &opt);
    diff_resolve_renames (results);

    return 0;
}