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
struct TYPE_4__ {int /*<<< orphan*/  list_head; } ;
typedef  TYPE_1__ list_t ;
typedef  int /*<<< orphan*/  list_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  list_insert_after_node (TYPE_1__*,int /*<<< orphan*/ *,void*) ; 

void
list_insert_head(list_t *list, void *object)
{
	list_node_t *lold = &list->list_head;
	list_insert_after_node(list, lold, object);
}