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
struct TYPE_3__ {int capacity; void* items; scalar_t__ length; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */
 void* malloc (int) ; 

list_t *create_list(void) {
	list_t *list = malloc(sizeof(list_t));
	if (!list) {
		return NULL;
	}
	list->capacity = 10;
	list->length = 0;
	list->items = malloc(sizeof(void*) * list->capacity);
	return list;
}