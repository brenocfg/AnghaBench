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
struct sway_container {scalar_t__ view; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_is_floating_or_child (struct sway_container*) ; 

__attribute__((used)) static void count_tiling_views(struct sway_container *con, void *data) {
	if (con->view && !container_is_floating_or_child(con)) {
		size_t *count = data;
		*count += 1;
	}
}