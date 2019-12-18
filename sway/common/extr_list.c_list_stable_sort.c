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
struct TYPE_4__ {int length; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */
 int /*<<< orphan*/  list_inplace_sort (TYPE_1__*,int /*<<< orphan*/ ,int,int (*) (void const*,void const*)) ; 

void list_stable_sort(list_t *list, int compare(const void *a, const void *b)) {
	if (list->length > 1) {
		list_inplace_sort(list, 0, list->length - 1, compare);
	}
}