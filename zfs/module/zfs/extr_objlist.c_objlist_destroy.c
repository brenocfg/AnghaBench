#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ol_list; } ;
typedef  TYPE_1__ objlist_t ;
typedef  TYPE_1__ objlist_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_remove_head (int /*<<< orphan*/ *) ; 

void
objlist_destroy(objlist_t *list)
{
	for (objlist_node_t *n = list_remove_head(&list->ol_list);
	    n != NULL; n = list_remove_head(&list->ol_list)) {
		kmem_free(n, sizeof (*n));
	}
	list_destroy(&list->ol_list);
	kmem_free(list, sizeof (*list));
}