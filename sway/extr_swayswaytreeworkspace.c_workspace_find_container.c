#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sway_workspace {TYPE_1__* floating; TYPE_2__* tiling; } ;
struct sway_container {int dummy; } ;
struct TYPE_4__ {int length; struct sway_container** items; } ;
struct TYPE_3__ {int length; struct sway_container** items; } ;

/* Variables and functions */
 struct sway_container* container_find_child (struct sway_container*,int (*) (struct sway_container*,void*),void*) ; 

struct sway_container *workspace_find_container(struct sway_workspace *ws,
		bool (*test)(struct sway_container *con, void *data), void *data) {
	struct sway_container *result = NULL;
	// Tiling
	for (int i = 0; i < ws->tiling->length; ++i) {
		struct sway_container *child = ws->tiling->items[i];
		if (test(child, data)) {
			return child;
		}
		if ((result = container_find_child(child, test, data))) {
			return result;
		}
	}
	// Floating
	for (int i = 0; i < ws->floating->length; ++i) {
		struct sway_container *child = ws->floating->items[i];
		if (test(child, data)) {
			return child;
		}
		if ((result = container_find_child(child, test, data))) {
			return result;
		}
	}
	return NULL;
}