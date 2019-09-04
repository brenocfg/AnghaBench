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
struct sway_workspace {struct sway_container* fullscreen; TYPE_1__* tiling; int /*<<< orphan*/  layout; } ;
struct sway_container {int /*<<< orphan*/  layout; } ;
struct TYPE_2__ {struct sway_container** items; scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_add_child (struct sway_container*,struct sway_container*) ; 
 struct sway_container* container_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  container_detach (struct sway_container*) ; 
 int /*<<< orphan*/  workspace_add_tiling (struct sway_workspace*,struct sway_container*) ; 

struct sway_container *workspace_wrap_children(struct sway_workspace *ws) {
	struct sway_container *fs = ws->fullscreen;
	struct sway_container *middle = container_create(NULL);
	middle->layout = ws->layout;
	while (ws->tiling->length) {
		struct sway_container *child = ws->tiling->items[0];
		container_detach(child);
		container_add_child(middle, child);
	}
	workspace_add_tiling(ws, middle);
	ws->fullscreen = fs;
	return middle;
}