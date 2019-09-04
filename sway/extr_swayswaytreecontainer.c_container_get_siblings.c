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
struct sway_container {TYPE_2__* workspace; TYPE_1__* parent; } ;
typedef  int /*<<< orphan*/  list_t ;
struct TYPE_4__ {int /*<<< orphan*/ * floating; int /*<<< orphan*/ * tiling; } ;
struct TYPE_3__ {int /*<<< orphan*/ * children; } ;

/* Variables and functions */
 scalar_t__ container_is_scratchpad_hidden (struct sway_container*) ; 
 int list_find (int /*<<< orphan*/ *,struct sway_container*) ; 

list_t *container_get_siblings(struct sway_container *container) {
	if (container->parent) {
		return container->parent->children;
	}
	if (container_is_scratchpad_hidden(container)) {
		return NULL;
	}
	if (list_find(container->workspace->tiling, container) != -1) {
		return container->workspace->tiling;
	}
	return container->workspace->floating;
}