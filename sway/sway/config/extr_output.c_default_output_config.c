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
struct wlr_output_mode {float refresh; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct wlr_output {struct sway_output* data; } ;
struct sway_output {int /*<<< orphan*/  detected_subpixel; } ;
struct output_config {int enabled; float refresh_rate; int x; int y; int scale; int /*<<< orphan*/  dpms_state; int /*<<< orphan*/  transform; int /*<<< orphan*/  subpixel; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPMS_ON ; 
 int /*<<< orphan*/  WL_OUTPUT_TRANSFORM_NORMAL ; 
 struct wlr_output_mode* wlr_output_preferred_mode (struct wlr_output*) ; 

__attribute__((used)) static void default_output_config(struct output_config *oc,
		struct wlr_output *wlr_output) {
	oc->enabled = 1;
	struct wlr_output_mode *mode = wlr_output_preferred_mode(wlr_output);
	if (mode != NULL) {
		oc->width = mode->width;
		oc->height = mode->height;
		oc->refresh_rate = mode->refresh / 1000.f;
	}
	oc->x = oc->y = -1;
	oc->scale = 1;
	struct sway_output *output = wlr_output->data;
	oc->subpixel = output->detected_subpixel;
	oc->transform = WL_OUTPUT_TRANSFORM_NORMAL;
	oc->dpms_state = DPMS_ON;
}