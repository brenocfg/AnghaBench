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
struct sway_view_child {int /*<<< orphan*/ * impl; } ;
struct TYPE_2__ {int /*<<< orphan*/  link; } ;
struct sway_subsurface {TYPE_1__ destroy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sway_subsurface*) ; 
 int /*<<< orphan*/  subsurface_impl ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void subsurface_destroy(struct sway_view_child *child) {
	if (!sway_assert(child->impl == &subsurface_impl,
			"Expected a subsurface")) {
		return;
	}
	struct sway_subsurface *subsurface = (struct sway_subsurface *)child;
	wl_list_remove(&subsurface->destroy.link);
	free(subsurface);
}