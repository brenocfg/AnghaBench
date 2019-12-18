#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  fs_mgr; } ;
struct TYPE_17__ {scalar_t__ status; int /*<<< orphan*/  name; int /*<<< orphan*/  sha1; } ;
struct TYPE_16__ {struct TYPE_16__* next; TYPE_2__* data; } ;
typedef  TYPE_1__ GList ;
typedef  int /*<<< orphan*/  GDestroyNotify ;
typedef  TYPE_2__ DiffEntry ;

/* Variables and functions */
 scalar_t__ DIFF_STATUS_DIR_ADDED ; 
 int /*<<< orphan*/  diff_entry_free (TYPE_2__*) ; 
 int /*<<< orphan*/  expand_dir_added_cb ; 
 TYPE_1__* g_list_concat (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* g_list_delete_link (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  g_list_free_full (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* g_list_reverse (TYPE_1__*) ; 
 int /*<<< orphan*/  rawdata_to_hex (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_4__* seaf ; 
 scalar_t__ seaf_fs_manager_traverse_path (int /*<<< orphan*/ ,char const*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 

__attribute__((used)) static int
expand_diff_results (const char *repo_id, int version,
                     const char *remote_root, const char *local_root,
                     GList **results)
{
    GList *ptr, *next;
    DiffEntry *de;
    char obj_id[41];
    GList *expanded = NULL;

    ptr = *results;
    while (ptr) {
        de = ptr->data;

        next = ptr->next;

        if (de->status == DIFF_STATUS_DIR_ADDED) {
            *results = g_list_delete_link (*results, ptr);

            rawdata_to_hex (de->sha1, obj_id, 20);
            if (seaf_fs_manager_traverse_path (seaf->fs_mgr,
                                               repo_id, version,
                                               remote_root,
                                               de->name,
                                               expand_dir_added_cb,
                                               &expanded) < 0) {
                diff_entry_free (de);
                goto error;
            }
            diff_entry_free (de);
        }

        ptr = next;
    }

    expanded = g_list_reverse (expanded);
    *results = g_list_concat (*results, expanded);

    return 0;

error:
    g_list_free_full (expanded, (GDestroyNotify)diff_entry_free);
    return -1;
}