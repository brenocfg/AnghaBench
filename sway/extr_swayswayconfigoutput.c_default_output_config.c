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
struct wlr_output_mode {int /*<<< orphan*/  refresh; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {int /*<<< orphan*/  prev; } ;
struct wlr_output {struct sway_output* data; TYPE_1__ modes; } ;
struct sway_output {int /*<<< orphan*/  detected_subpixel; } ;
struct output_config {int enabled; int x; int y; int scale; int /*<<< orphan*/  dpms_state; int /*<<< orphan*/  transform; int /*<<< orphan*/  subpixel; int /*<<< orphan*/  refresh_rate; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPMS_ON ; 
 int /*<<< orphan*/  WL_OUTPUT_TRANSFORM_NORMAL ; 
 int /*<<< orphan*/  link ; 
 struct wlr_output_mode* mode ; 
 struct wlr_output_mode* wl_container_of (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_empty (TYPE_1__*) ; 

__attribute__((used)) static void default_output_config(struct output_config *oc,
		struct wlr_output *wlr_output) {
	oc->enabled = 1;
	if (!wl_list_empty(&wlr_output->modes)) {
		struct wlr_output_mode *mode =
			wl_container_of(wlr_output->modes.prev, mode, link);
		oc->width = mode->width;
		oc->height = mode->height;
		oc->refresh_rate = mode->refresh;
	}
	oc->x = oc->y = -1;
	oc->scale = 1;
	struct sway_output *output = wlr_output->data;
	oc->subpixel = output->detected_subpixel;
	oc->transform = WL_OUTPUT_TRANSFORM_NORMAL;
	oc->dpms_state = DPMS_ON;
}