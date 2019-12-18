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
struct libinput_device {int dummy; } ;
struct input_config {scalar_t__ send_events; scalar_t__ tap; scalar_t__ tap_button_map; scalar_t__ drag; scalar_t__ drag_lock; scalar_t__ pointer_accel; scalar_t__ accel_profile; scalar_t__ natural_scroll; scalar_t__ left_handed; scalar_t__ click_method; scalar_t__ middle_emulation; scalar_t__ scroll_method; scalar_t__ scroll_button; scalar_t__ dwt; int /*<<< orphan*/  identifier; } ;

/* Variables and functions */
 scalar_t__ FLT_MIN ; 
 scalar_t__ INT_MIN ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int set_accel_profile (struct libinput_device*,scalar_t__) ; 
 int set_accel_speed (struct libinput_device*,scalar_t__) ; 
 int set_click_method (struct libinput_device*,scalar_t__) ; 
 int set_dwt (struct libinput_device*,scalar_t__) ; 
 int set_left_handed (struct libinput_device*,scalar_t__) ; 
 int set_middle_emulation (struct libinput_device*,scalar_t__) ; 
 int set_natural_scroll (struct libinput_device*,scalar_t__) ; 
 int set_scroll_button (struct libinput_device*,scalar_t__) ; 
 int set_scroll_method (struct libinput_device*,scalar_t__) ; 
 int set_send_events (struct libinput_device*,scalar_t__) ; 
 int set_tap (struct libinput_device*,scalar_t__) ; 
 int set_tap_button_map (struct libinput_device*,scalar_t__) ; 
 int set_tap_drag (struct libinput_device*,scalar_t__) ; 
 int set_tap_drag_lock (struct libinput_device*,scalar_t__) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool config_libinput_pointer(struct libinput_device *device,
		struct input_config *ic, const char *device_id) {
	sway_log(SWAY_DEBUG, "config_libinput_pointer('%s' on  '%s')",
			ic->identifier, device_id);
	bool changed = false;
	if (ic->send_events != INT_MIN) {
		changed |= set_send_events(device, ic->send_events);
	}
	if (ic->tap != INT_MIN) {
		changed |= set_tap(device, ic->tap);
	}
	if (ic->tap_button_map != INT_MIN) {
		changed |= set_tap_button_map(device, ic->tap_button_map);
	}
	if (ic->drag != INT_MIN) {
		changed |= set_tap_drag(device, ic->drag);
	}
	if (ic->drag_lock != INT_MIN) {
		changed |= set_tap_drag_lock(device, ic->drag_lock);
	}

	if (ic->pointer_accel != FLT_MIN) {
		changed |= set_accel_speed(device, ic->pointer_accel);
	}
	if (ic->accel_profile != INT_MIN) {
		changed |= set_accel_profile(device, ic->accel_profile);
	}
	if (ic->natural_scroll != INT_MIN) {
		changed |= set_natural_scroll(device, ic->natural_scroll);
	}
	if (ic->left_handed != INT_MIN) {
		changed |= set_left_handed(device, ic->left_handed);
	}
	if (ic->click_method != INT_MIN) {
		changed |= set_click_method(device, ic->click_method);
	}
	if (ic->middle_emulation != INT_MIN) {
		changed |= set_middle_emulation(device, ic->middle_emulation);
	}
	if (ic->scroll_method != INT_MIN) {
		changed |= set_scroll_method(device, ic->scroll_method);
	}
	if (ic->scroll_button != INT_MIN) {
		changed |= set_scroll_button(device, ic->scroll_button);
	}
	if (ic->dwt != INT_MIN) {
		changed |= set_dwt(device, ic->dwt);
	}
	return changed;
}