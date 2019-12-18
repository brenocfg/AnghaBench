#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sway_surface_iterator_func_t ;
struct TYPE_5__ {TYPE_1__* floating; struct sway_container* fullscreen; } ;
struct sway_workspace {TYPE_2__ current; } ;
struct sway_output {int /*<<< orphan*/ * layers; } ;
struct sway_container {int dummy; } ;
struct surface_iterator_data {void* user_data; struct sway_output* output; int /*<<< orphan*/  user_iterator; } ;
struct TYPE_6__ {int /*<<< orphan*/  drag_icons; int /*<<< orphan*/  xwayland_unmanaged; struct sway_container* fullscreen_global; } ;
struct TYPE_4__ {int length; struct sway_container** items; } ;

/* Variables and functions */
 size_t ZWLR_LAYER_SHELL_V1_LAYER_BACKGROUND ; 
 size_t ZWLR_LAYER_SHELL_V1_LAYER_BOTTOM ; 
 size_t ZWLR_LAYER_SHELL_V1_LAYER_OVERLAY ; 
 size_t ZWLR_LAYER_SHELL_V1_LAYER_TOP ; 
 int /*<<< orphan*/  container_for_each_child (struct sway_container*,int /*<<< orphan*/  (*) (struct sway_container*,struct surface_iterator_data*),struct surface_iterator_data*) ; 
 scalar_t__ container_is_transient_for (struct sway_container*,struct sway_container*) ; 
 int /*<<< orphan*/  for_each_surface_container_iterator (struct sway_container*,struct surface_iterator_data*) ; 
 int /*<<< orphan*/  output_drag_icons_for_each_surface (struct sway_output*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 struct sway_workspace* output_get_active_workspace (struct sway_output*) ; 
 scalar_t__ output_has_opaque_overlay_layer_surface (struct sway_output*) ; 
 int /*<<< orphan*/  output_layer_for_each_surface (struct sway_output*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  output_unmanaged_for_each_surface (struct sway_output*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 TYPE_3__* root ; 
 int /*<<< orphan*/  workspace_for_each_container (struct sway_workspace*,int /*<<< orphan*/  (*) (struct sway_container*,struct surface_iterator_data*),struct surface_iterator_data*) ; 

__attribute__((used)) static void output_for_each_surface(struct sway_output *output,
		sway_surface_iterator_func_t iterator, void *user_data) {
	if (output_has_opaque_overlay_layer_surface(output)) {
		goto overlay;
	}

	struct surface_iterator_data data = {
		.user_iterator = iterator,
		.user_data = user_data,
		.output = output,
	};

	struct sway_workspace *workspace = output_get_active_workspace(output);
	struct sway_container *fullscreen_con = root->fullscreen_global;
	if (!fullscreen_con) {
		if (!workspace) {
			return;
		}
		fullscreen_con = workspace->current.fullscreen;
	}
	if (fullscreen_con) {
		for_each_surface_container_iterator(fullscreen_con, &data);
		container_for_each_child(fullscreen_con,
			for_each_surface_container_iterator, &data);

		// TODO: Show transient containers for fullscreen global
		if (fullscreen_con == workspace->current.fullscreen) {
			for (int i = 0; i < workspace->current.floating->length; ++i) {
				struct sway_container *floater =
					workspace->current.floating->items[i];
				if (container_is_transient_for(floater, fullscreen_con)) {
					for_each_surface_container_iterator(floater, &data);
				}
			}
		}
#if HAVE_XWAYLAND
		output_unmanaged_for_each_surface(output, &root->xwayland_unmanaged,
			iterator, user_data);
#endif
	} else {
		output_layer_for_each_surface(output,
			&output->layers[ZWLR_LAYER_SHELL_V1_LAYER_BACKGROUND],
			iterator, user_data);
		output_layer_for_each_surface(output,
			&output->layers[ZWLR_LAYER_SHELL_V1_LAYER_BOTTOM],
			iterator, user_data);

		workspace_for_each_container(workspace,
			for_each_surface_container_iterator, &data);

#if HAVE_XWAYLAND
		output_unmanaged_for_each_surface(output, &root->xwayland_unmanaged,
			iterator, user_data);
#endif
		output_layer_for_each_surface(output,
			&output->layers[ZWLR_LAYER_SHELL_V1_LAYER_TOP],
			iterator, user_data);
	}

overlay:
	output_layer_for_each_surface(output,
		&output->layers[ZWLR_LAYER_SHELL_V1_LAYER_OVERLAY],
		iterator, user_data);
	output_drag_icons_for_each_surface(output, &root->drag_icons,
		iterator, user_data);
}