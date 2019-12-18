#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int length; void const** items; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */

int list_find(list_t *list, const void *item) {
	for (int i = 0; i < list->length; i++) {
		if (list->items[i] == item) {
			return i;
		}
	}
	return -1;
}