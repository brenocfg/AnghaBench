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
struct sway_container {struct sway_container* parent; scalar_t__ fullscreen_mode; } ;

/* Variables and functions */

bool container_is_fullscreen_or_child(struct sway_container *container) {
	do {
		if (container->fullscreen_mode) {
			return true;
		}
		container = container->parent;
	} while (container);

	return false;
}