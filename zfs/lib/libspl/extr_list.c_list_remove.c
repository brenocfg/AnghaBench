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
typedef  int /*<<< orphan*/  list_t ;
struct TYPE_4__ {int /*<<< orphan*/ * list_next; } ;
typedef  TYPE_1__ list_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_1__* list_d2l (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove_node (TYPE_1__*) ; 

void
list_remove(list_t *list, void *object)
{
	list_node_t *lold = list_d2l(list, object);
	ASSERT(!list_empty(list));
	ASSERT(lold->list_next != NULL);
	list_remove_node(lold);
}