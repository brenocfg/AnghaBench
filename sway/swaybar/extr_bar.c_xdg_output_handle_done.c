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
struct zxdg_output_v1 {int dummy; } ;
struct swaybar_output {int /*<<< orphan*/  surface; int /*<<< orphan*/  link; int /*<<< orphan*/ * name; struct swaybar* bar; } ;
struct swaybar {TYPE_1__* config; scalar_t__ running; int /*<<< orphan*/  compositor; int /*<<< orphan*/  outputs; int /*<<< orphan*/  unused_outputs; } ;
struct TYPE_2__ {scalar_t__ workspace_buttons; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bar_uses_output (struct swaybar_output*) ; 
 int /*<<< orphan*/  determine_bar_visibility (struct swaybar*,int) ; 
 int /*<<< orphan*/  ipc_get_workspaces (struct swaybar*) ; 
 int /*<<< orphan*/  wl_compositor_create_surface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xdg_output_handle_done(void *data,
		struct zxdg_output_v1 *xdg_output) {
	struct swaybar_output *output = data;
	struct swaybar *bar = output->bar;

	if (!wl_list_empty(&output->link)) {
		return;
	}

	assert(output->name != NULL);
	if (!bar_uses_output(output)) {
		wl_list_remove(&output->link);
		wl_list_insert(&bar->unused_outputs, &output->link);
		return;
	}

	wl_list_remove(&output->link);
	wl_list_insert(&bar->outputs, &output->link);

	output->surface = wl_compositor_create_surface(bar->compositor);
	assert(output->surface);

	determine_bar_visibility(bar, false);

	if (bar->running && bar->config->workspace_buttons) {
		ipc_get_workspaces(bar);
	}
}