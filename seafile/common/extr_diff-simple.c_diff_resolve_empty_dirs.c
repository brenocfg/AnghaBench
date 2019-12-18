#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ status; } ;
struct TYPE_13__ {TYPE_2__* data; struct TYPE_13__* next; } ;
typedef  TYPE_1__ GList ;
typedef  TYPE_2__ DiffEntry ;

/* Variables and functions */
 scalar_t__ DIFF_STATUS_DIR_ADDED ; 
 scalar_t__ DIFF_STATUS_DIR_DELETED ; 
 TYPE_1__* g_list_delete_link (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  g_list_free (TYPE_1__*) ; 
 TYPE_1__* g_list_prepend (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ is_redundant_empty_dir (TYPE_2__*,TYPE_2__*) ; 

void
diff_resolve_empty_dirs (GList **diff_entries)
{
    GList *empty_dirs = NULL;
    GList *p, *dir, *file;
    DiffEntry *de, *de_dir, *de_file;

    for (p = *diff_entries; p != NULL; p = p->next) {
        de = p->data;
        if (de->status == DIFF_STATUS_DIR_ADDED ||
            de->status == DIFF_STATUS_DIR_DELETED)
            empty_dirs = g_list_prepend (empty_dirs, p);
    }

    for (dir = empty_dirs; dir != NULL; dir = dir->next) {
        de_dir = ((GList *)dir->data)->data;
        for (file = *diff_entries; file != NULL; file = file->next) {
            de_file = file->data;
            if (is_redundant_empty_dir (de_dir, de_file)) {
                *diff_entries = g_list_delete_link (*diff_entries, dir->data);
                break;
            }
        }
    }

    g_list_free (empty_dirs);
}