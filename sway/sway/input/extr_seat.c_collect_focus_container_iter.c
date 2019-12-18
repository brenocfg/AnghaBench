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
struct sway_container {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  collect_focus_iter (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void collect_focus_container_iter(struct sway_container *container,
		void *data) {
	collect_focus_iter(&container->node, data);
}