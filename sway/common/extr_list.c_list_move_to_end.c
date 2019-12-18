#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int length; void** items; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  list_del (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 

void list_move_to_end(list_t *list, void *item) {
	int i;
	for (i = 0; i < list->length; ++i) {
		if (list->items[i] == item) {
			break;
		}
	}
	if (!sway_assert(i < list->length, "Item not found in list")) {
		return;
	}
	list_del(list, i);
	list_add(list, item);
}