#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  permission; int /*<<< orphan*/  path; } ;
struct TYPE_9__ {TYPE_2__* data; struct TYPE_9__* next; } ;
typedef  TYPE_1__ GList ;
typedef  TYPE_2__ FolderPerm ;

/* Variables and functions */
 TYPE_2__* folder_perm_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* g_list_append (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static GList *
folder_perm_list_copy (GList *perms)
{
    GList *ret = NULL, *ptr;
    FolderPerm *perm, *new_perm;

    for (ptr = perms; ptr; ptr = ptr->next) {
        perm = ptr->data;
        new_perm = folder_perm_new (perm->path, perm->permission);
        ret = g_list_append (ret, new_perm);
    }

    return ret;
}