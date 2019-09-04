#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; struct TYPE_4__* next; } ;
typedef  TYPE_1__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_list_free (TYPE_1__*) ; 

void seaf_repo_free_ignore_files (GList *ignore_list)
{
    GList *p;

    if (ignore_list == NULL)
        return;

    for (p = ignore_list; p != NULL; p = p->next)
        free(p->data);

    g_list_free (ignore_list);
}