#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; scalar_t__ data; } ;
struct TYPE_6__ {struct TYPE_6__* ondisk; TYPE_2__* entries; } ;
typedef  int /*<<< orphan*/  SeafDirent ;
typedef  TYPE_1__ SeafDir ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_list_free (TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_dirent_free (int /*<<< orphan*/ *) ; 

void
seaf_dir_free (SeafDir *dir)
{
    if (dir == NULL)
        return;

    GList *ptr = dir->entries;
    while (ptr) {
        seaf_dirent_free ((SeafDirent *)ptr->data);
        ptr = ptr->next;
    }

    g_list_free (dir->entries);
    g_free (dir->ondisk);
    g_free(dir);
}