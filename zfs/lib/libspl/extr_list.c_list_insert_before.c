#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  list_t ;
typedef  int /*<<< orphan*/  list_node_t ;

/* Variables and functions */
 int /*<<< orphan*/ * list_d2l (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  list_insert_before_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  list_insert_tail (int /*<<< orphan*/ *,void*) ; 

void
list_insert_before(list_t *list, void *object, void *nobject)
{
	if (object == NULL) {
		list_insert_tail(list, nobject);
	} else {
		list_node_t *lold = list_d2l(list, object);
		list_insert_before_node(list, lold, nobject);
	}
}