#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  version; int /*<<< orphan*/  dents; } ;
struct TYPE_11__ {int /*<<< orphan*/ * data; struct TYPE_11__* next; } ;
typedef  int /*<<< orphan*/  SeafDirent ;
typedef  int /*<<< orphan*/  SeafDir ;
typedef  TYPE_1__ GList ;
typedef  int /*<<< orphan*/  ChangeSetDirent ;
typedef  TYPE_2__ ChangeSetDir ;

/* Variables and functions */
 int /*<<< orphan*/ * changeset_dirent_to_seaf_dirent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compare_dents ; 
 TYPE_1__* g_hash_table_get_values (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_list_free (TYPE_1__*) ; 
 TYPE_1__* g_list_prepend (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* g_list_sort (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * seaf_dir_new (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SeafDir *
changeset_dir_to_seaf_dir (ChangeSetDir *dir)
{
    GList *dents = NULL, *seaf_dents = NULL;
    GList *ptr;
    ChangeSetDirent *dent;
    SeafDirent *seaf_dent;
    SeafDir *seaf_dir;

    dents = g_hash_table_get_values (dir->dents);
    for (ptr = dents; ptr; ptr = ptr->next) {
        dent = ptr->data;
        seaf_dent = changeset_dirent_to_seaf_dirent (dir->version, dent);
        seaf_dents = g_list_prepend (seaf_dents, seaf_dent);
    }
    /* Sort it in descending order. */
    seaf_dents = g_list_sort (seaf_dents, compare_dents);

    /* seaf_dir_new() computes the dir id. */
    seaf_dir = seaf_dir_new (NULL, seaf_dents, dir->version);

    g_list_free (dents);
    return seaf_dir;
}