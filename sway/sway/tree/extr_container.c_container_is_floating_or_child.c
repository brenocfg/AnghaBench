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
struct sway_container {struct sway_container* parent; } ;

/* Variables and functions */
 int container_is_floating (struct sway_container*) ; 

bool container_is_floating_or_child(struct sway_container *container) {
	while (container->parent) {
		container = container->parent;
	}
	return container_is_floating(container);
}