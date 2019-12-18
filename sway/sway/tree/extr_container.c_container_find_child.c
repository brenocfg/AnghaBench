#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sway_container {TYPE_1__* children; } ;
struct TYPE_2__ {int length; struct sway_container** items; } ;

/* Variables and functions */

struct sway_container *container_find_child(struct sway_container *container,
		bool (*test)(struct sway_container *con, void *data), void *data) {
	if (!container->children) {
		return NULL;
	}
	for (int i = 0; i < container->children->length; ++i) {
		struct sway_container *child = container->children->items[i];
		if (test(child, data)) {
			return child;
		}
		struct sway_container *res = container_find_child(child, test, data);
		if (res) {
			return res;
		}
	}
	return NULL;
}