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
struct sway_container {scalar_t__ scratchpad; TYPE_1__* workspace; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  floating; } ;

/* Variables and functions */
 int list_find (int /*<<< orphan*/ ,struct sway_container*) ; 

bool container_is_floating(struct sway_container *container) {
	if (!container->parent && container->workspace &&
			list_find(container->workspace->floating, container) != -1) {
		return true;
	}
	if (container->scratchpad) {
		return true;
	}
	return false;
}