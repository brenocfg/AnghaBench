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
 int /*<<< orphan*/  g_list_free (TYPE_1__*) ; 
 int /*<<< orphan*/  seaf_branch_unref (int /*<<< orphan*/ ) ; 

void
seaf_branch_list_free (GList *blist)
{
    GList *ptr;

    for (ptr = blist; ptr; ptr = ptr->next) {
        seaf_branch_unref (ptr->data);
    }
    g_list_free (blist);
}