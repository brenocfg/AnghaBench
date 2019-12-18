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
struct wlr_box {int dummy; } ;
struct input_config_mapped_from_region {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * matrix; scalar_t__ configured; } ;
struct input_config {scalar_t__ accel_profile; scalar_t__ click_method; scalar_t__ drag; scalar_t__ drag_lock; scalar_t__ dwt; scalar_t__ left_handed; scalar_t__ middle_emulation; scalar_t__ natural_scroll; scalar_t__ pointer_accel; scalar_t__ scroll_factor; scalar_t__ repeat_delay; scalar_t__ repeat_rate; scalar_t__ scroll_method; scalar_t__ scroll_button; scalar_t__ send_events; scalar_t__ tap; scalar_t__ tap_button_map; scalar_t__ xkb_numlock; scalar_t__ xkb_capslock; TYPE_1__ calibration_matrix; int /*<<< orphan*/ * mapped_to_region; int /*<<< orphan*/ * mapped_to_output; scalar_t__ mapped_to; int /*<<< orphan*/ * mapped_from_region; int /*<<< orphan*/ * xkb_variant; int /*<<< orphan*/ * xkb_rules; int /*<<< orphan*/ * xkb_options; int /*<<< orphan*/ * xkb_model; int /*<<< orphan*/ * xkb_layout; int /*<<< orphan*/ * xkb_file; scalar_t__ xkb_file_is_set; } ;

/* Variables and functions */
 scalar_t__ FLT_MIN ; 
 scalar_t__ INT_MIN ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ *) ; 

void merge_input_config(struct input_config *dst, struct input_config *src) {
	if (src->accel_profile != INT_MIN) {
		dst->accel_profile = src->accel_profile;
	}
	if (src->click_method != INT_MIN) {
		dst->click_method = src->click_method;
	}
	if (src->drag != INT_MIN) {
		dst->drag = src->drag;
	}
	if (src->drag_lock != INT_MIN) {
		dst->drag_lock = src->drag_lock;
	}
	if (src->dwt != INT_MIN) {
		dst->dwt = src->dwt;
	}
	if (src->left_handed != INT_MIN) {
		dst->left_handed = src->left_handed;
	}
	if (src->middle_emulation != INT_MIN) {
		dst->middle_emulation = src->middle_emulation;
	}
	if (src->natural_scroll != INT_MIN) {
		dst->natural_scroll = src->natural_scroll;
	}
	if (src->pointer_accel != FLT_MIN) {
		dst->pointer_accel = src->pointer_accel;
	}
	if (src->scroll_factor != FLT_MIN) {
		dst->scroll_factor = src->scroll_factor;
	}
	if (src->repeat_delay != INT_MIN) {
		dst->repeat_delay = src->repeat_delay;
	}
	if (src->repeat_rate != INT_MIN) {
		dst->repeat_rate = src->repeat_rate;
	}
	if (src->scroll_method != INT_MIN) {
		dst->scroll_method = src->scroll_method;
	}
	if (src->scroll_button != INT_MIN) {
		dst->scroll_button = src->scroll_button;
	}
	if (src->send_events != INT_MIN) {
		dst->send_events = src->send_events;
	}
	if (src->tap != INT_MIN) {
		dst->tap = src->tap;
	}
	if (src->tap_button_map != INT_MIN) {
		dst->tap_button_map = src->tap_button_map;
	}
	if (src->xkb_file_is_set) {
		free(dst->xkb_file);
		dst->xkb_file = src->xkb_file ? strdup(src->xkb_file) : NULL;
		dst->xkb_file_is_set = dst->xkb_file != NULL;
	}
	if (src->xkb_layout) {
		free(dst->xkb_layout);
		dst->xkb_layout = strdup(src->xkb_layout);
	}
	if (src->xkb_model) {
		free(dst->xkb_model);
		dst->xkb_model = strdup(src->xkb_model);
	}
	if (src->xkb_options) {
		free(dst->xkb_options);
		dst->xkb_options = strdup(src->xkb_options);
	}
	if (src->xkb_rules) {
		free(dst->xkb_rules);
		dst->xkb_rules = strdup(src->xkb_rules);
	}
	if (src->xkb_variant) {
		free(dst->xkb_variant);
		dst->xkb_variant = strdup(src->xkb_variant);
	}
	if (src->xkb_numlock != INT_MIN) {
		dst->xkb_numlock = src->xkb_numlock;
	}
	if (src->xkb_capslock != INT_MIN) {
		dst->xkb_capslock = src->xkb_capslock;
	}
	if (src->mapped_from_region) {
		free(dst->mapped_from_region);
		dst->mapped_from_region =
			malloc(sizeof(struct input_config_mapped_from_region));
		memcpy(dst->mapped_from_region, src->mapped_from_region,
			sizeof(struct input_config_mapped_from_region));
	}
	if (src->mapped_to) {
		dst->mapped_to = src->mapped_to;
	}
	if (src->mapped_to_output) {
		free(dst->mapped_to_output);
		dst->mapped_to_output = strdup(src->mapped_to_output);
	}
	if (src->mapped_to_region) {
		free(dst->mapped_to_region);
		dst->mapped_to_region =
			malloc(sizeof(struct wlr_box));
		memcpy(dst->mapped_to_region, src->mapped_to_region,
			sizeof(struct wlr_box));
	}
	if (src->calibration_matrix.configured) {
		dst->calibration_matrix.configured = src->calibration_matrix.configured;
		memcpy(dst->calibration_matrix.matrix, src->calibration_matrix.matrix,
			sizeof(src->calibration_matrix.matrix));
	}
}