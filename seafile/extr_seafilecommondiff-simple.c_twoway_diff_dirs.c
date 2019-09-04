#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_6__ {scalar_t__ fold_dir_diff; int /*<<< orphan*/ ** results; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ SeafDirent ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  DiffEntry ;
typedef  TYPE_2__ DiffData ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_STATUS_DIR_ADDED ; 
 int /*<<< orphan*/  DIFF_STATUS_DIR_DELETED ; 
 int /*<<< orphan*/  DIFF_TYPE_COMMITS ; 
 int /*<<< orphan*/  EMPTY_SHA1 ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * diff_entry_new_from_dirent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/ * g_list_prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
twoway_diff_dirs (int n, const char *basedir, SeafDirent *dirs[], void *vdata,
                  gboolean *recurse)
{
    DiffData *data = vdata;
    GList **results = data->results;
    DiffEntry *de;
    SeafDirent *tree1 = dirs[0];
    SeafDirent *tree2 = dirs[1];

    if (!tree1) {
        if (strcmp (tree2->id, EMPTY_SHA1) == 0 || data->fold_dir_diff) {
            de = diff_entry_new_from_dirent (DIFF_TYPE_COMMITS, DIFF_STATUS_DIR_ADDED,
                                             tree2, basedir);
            *results = g_list_prepend (*results, de);
            *recurse = FALSE;
        } else
            *recurse = TRUE;
        return 0;
    }

    if (!tree2) {
        de = diff_entry_new_from_dirent (DIFF_TYPE_COMMITS,
                                         DIFF_STATUS_DIR_DELETED,
                                         tree1, basedir);
        *results = g_list_prepend (*results, de);

        if (data->fold_dir_diff) {
            *recurse = FALSE;
        } else
            *recurse = TRUE;
        return 0;
    }

    return 0;
}