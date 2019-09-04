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
struct swaybar_output {struct swaybar_output* identifier; struct swaybar_output* name; int /*<<< orphan*/  link; int /*<<< orphan*/  workspaces; int /*<<< orphan*/  hotspots; int /*<<< orphan*/ * buffers; int /*<<< orphan*/  output; int /*<<< orphan*/  xdg_output; int /*<<< orphan*/ * input_region; int /*<<< orphan*/ * surface; int /*<<< orphan*/ * layer_surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  destroy_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct swaybar_output*) ; 
 int /*<<< orphan*/  free_hotspots (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_workspaces (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,struct swaybar_output*) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_output_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_region_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zwlr_layer_surface_v1_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zxdg_output_v1_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void swaybar_output_free(struct swaybar_output *output) {
	if (!output) {
		return;
	}
	sway_log(SWAY_DEBUG, "Removing output %s", output->name);
	if (output->layer_surface != NULL) {
		zwlr_layer_surface_v1_destroy(output->layer_surface);
	}
	if (output->surface != NULL) {
		wl_surface_destroy(output->surface);
	}
	if (output->input_region != NULL) {
		wl_region_destroy(output->input_region);
	}
	zxdg_output_v1_destroy(output->xdg_output);
	wl_output_destroy(output->output);
	destroy_buffer(&output->buffers[0]);
	destroy_buffer(&output->buffers[1]);
	free_hotspots(&output->hotspots);
	free_workspaces(&output->workspaces);
	wl_list_remove(&output->link);
	free(output->name);
	free(output->identifier);
	free(output);
}