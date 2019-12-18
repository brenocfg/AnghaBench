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
struct swaybar_output {scalar_t__ layer_surface; scalar_t__ input_region; int /*<<< orphan*/  surface; int /*<<< orphan*/  output; struct swaybar* bar; } ;
struct swaybar_config {int /*<<< orphan*/  position; int /*<<< orphan*/  mode; } ;
struct swaybar {int /*<<< orphan*/  compositor; int /*<<< orphan*/  layer_shell; struct swaybar_config* config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZWLR_LAYER_SHELL_V1_LAYER_BOTTOM ; 
 int /*<<< orphan*/  ZWLR_LAYER_SHELL_V1_LAYER_OVERLAY ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  layer_surface_listener ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wl_compositor_create_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_set_input_region (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ zwlr_layer_shell_v1_get_layer_surface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zwlr_layer_surface_v1_add_listener (scalar_t__,int /*<<< orphan*/ *,struct swaybar_output*) ; 
 int /*<<< orphan*/  zwlr_layer_surface_v1_set_anchor (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zwlr_layer_surface_v1_set_exclusive_zone (scalar_t__,int) ; 

__attribute__((used)) static void add_layer_surface(struct swaybar_output *output) {
	if (output->layer_surface) {
		return;
	}
	struct swaybar *bar = output->bar;

	struct swaybar_config *config = bar->config;
	bool hidden = strcmp(config->mode, "hide") == 0;
	bool overlay = !hidden && strcmp(config->mode, "overlay") == 0;
	output->layer_surface = zwlr_layer_shell_v1_get_layer_surface(
			bar->layer_shell, output->surface, output->output,
			hidden || overlay ? ZWLR_LAYER_SHELL_V1_LAYER_OVERLAY :
			ZWLR_LAYER_SHELL_V1_LAYER_BOTTOM, "panel");
	assert(output->layer_surface);
	zwlr_layer_surface_v1_add_listener(output->layer_surface,
			&layer_surface_listener, output);

	if (overlay) {
		// Empty input region
		output->input_region = wl_compositor_create_region(bar->compositor);
		assert(output->input_region);

		wl_surface_set_input_region(output->surface, output->input_region);
	}

	zwlr_layer_surface_v1_set_anchor(output->layer_surface, config->position);
	if (hidden || overlay) {
		zwlr_layer_surface_v1_set_exclusive_zone(output->layer_surface, -1);
	}
}