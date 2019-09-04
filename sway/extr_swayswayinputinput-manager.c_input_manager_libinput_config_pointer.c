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
struct wlr_input_device {int dummy; } ;
struct sway_input_device {struct wlr_input_device* wlr_device; } ;
struct libinput_device {int dummy; } ;
struct input_config {scalar_t__ accel_profile; scalar_t__ click_method; scalar_t__ drag; scalar_t__ drag_lock; scalar_t__ dwt; scalar_t__ left_handed; scalar_t__ middle_emulation; scalar_t__ natural_scroll; scalar_t__ pointer_accel; scalar_t__ scroll_button; scalar_t__ scroll_method; scalar_t__ send_events; scalar_t__ tap; scalar_t__ tap_button_map; int /*<<< orphan*/  identifier; } ;

/* Variables and functions */
 scalar_t__ FLT_MIN ; 
 scalar_t__ INT_MIN ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 struct input_config* input_device_get_config (struct sway_input_device*) ; 
 int /*<<< orphan*/  libinput_device_config_accel_set_profile (struct libinput_device*,scalar_t__) ; 
 int /*<<< orphan*/  libinput_device_config_accel_set_speed (struct libinput_device*,scalar_t__) ; 
 int /*<<< orphan*/  libinput_device_config_click_set_method (struct libinput_device*,scalar_t__) ; 
 int /*<<< orphan*/  libinput_device_config_dwt_set_enabled (struct libinput_device*,scalar_t__) ; 
 int /*<<< orphan*/  libinput_device_config_left_handed_set (struct libinput_device*,scalar_t__) ; 
 int /*<<< orphan*/  libinput_device_config_middle_emulation_set_enabled (struct libinput_device*,scalar_t__) ; 
 int /*<<< orphan*/  libinput_device_config_scroll_set_button (struct libinput_device*,scalar_t__) ; 
 int /*<<< orphan*/  libinput_device_config_scroll_set_method (struct libinput_device*,scalar_t__) ; 
 int /*<<< orphan*/  libinput_device_config_scroll_set_natural_scroll_enabled (struct libinput_device*,scalar_t__) ; 
 int /*<<< orphan*/  libinput_device_config_send_events_set_mode (struct libinput_device*,scalar_t__) ; 
 int /*<<< orphan*/  libinput_device_config_tap_set_button_map (struct libinput_device*,scalar_t__) ; 
 int /*<<< orphan*/  libinput_device_config_tap_set_drag_enabled (struct libinput_device*,scalar_t__) ; 
 int /*<<< orphan*/  libinput_device_config_tap_set_drag_lock_enabled (struct libinput_device*,scalar_t__) ; 
 int /*<<< orphan*/  libinput_device_config_tap_set_enabled (struct libinput_device*,scalar_t__) ; 
 int /*<<< orphan*/  log_libinput_config_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wlr_input_device_is_libinput (struct wlr_input_device*) ; 
 struct libinput_device* wlr_libinput_get_device_handle (struct wlr_input_device*) ; 

__attribute__((used)) static void input_manager_libinput_config_pointer(
		struct sway_input_device *input_device) {
	struct wlr_input_device *wlr_device = input_device->wlr_device;
	struct input_config *ic = input_device_get_config(input_device);
	struct libinput_device *libinput_device;

	if (!ic || !wlr_input_device_is_libinput(wlr_device)) {
		return;
	}

	libinput_device = wlr_libinput_get_device_handle(wlr_device);
	sway_log(SWAY_DEBUG, "input_manager_libinput_config_pointer(%s)",
		ic->identifier);

	if (ic->accel_profile != INT_MIN) {
		sway_log(SWAY_DEBUG, "libinput_config_pointer(%s) accel_set_profile(%d)",
			ic->identifier, ic->accel_profile);
		log_libinput_config_status(libinput_device_config_accel_set_profile(
					libinput_device, ic->accel_profile));
	}
	if (ic->click_method != INT_MIN) {
		sway_log(SWAY_DEBUG, "libinput_config_pointer(%s) click_set_method(%d)",
			ic->identifier, ic->click_method);
		log_libinput_config_status(libinput_device_config_click_set_method(
					libinput_device, ic->click_method));
	}
	if (ic->drag != INT_MIN) {
		sway_log(SWAY_DEBUG,
			"libinput_config_pointer(%s) tap_set_drag_enabled(%d)",
			ic->identifier, ic->drag);
		log_libinput_config_status(libinput_device_config_tap_set_drag_enabled(
					libinput_device, ic->drag));
	}
	if (ic->drag_lock != INT_MIN) {
		sway_log(SWAY_DEBUG,
			"libinput_config_pointer(%s) tap_set_drag_lock_enabled(%d)",
			ic->identifier, ic->drag_lock);
		log_libinput_config_status(
				libinput_device_config_tap_set_drag_lock_enabled(
					libinput_device, ic->drag_lock));
	}
	if (ic->dwt != INT_MIN) {
		sway_log(SWAY_DEBUG, "libinput_config_pointer(%s) dwt_set_enabled(%d)",
			ic->identifier, ic->dwt);
		log_libinput_config_status(libinput_device_config_dwt_set_enabled(
					libinput_device, ic->dwt));
	}
	if (ic->left_handed != INT_MIN) {
		sway_log(SWAY_DEBUG,
			"libinput_config_pointer(%s) left_handed_set_enabled(%d)",
			ic->identifier, ic->left_handed);
		log_libinput_config_status(libinput_device_config_left_handed_set(
					libinput_device, ic->left_handed));
	}
	if (ic->middle_emulation != INT_MIN) {
		sway_log(SWAY_DEBUG,
			"libinput_config_pointer(%s) middle_emulation_set_enabled(%d)",
			ic->identifier, ic->middle_emulation);
		log_libinput_config_status(
				libinput_device_config_middle_emulation_set_enabled(
					libinput_device, ic->middle_emulation));
	}
	if (ic->natural_scroll != INT_MIN) {
		sway_log(SWAY_DEBUG,
			"libinput_config_pointer(%s) natural_scroll_set_enabled(%d)",
			ic->identifier, ic->natural_scroll);
		log_libinput_config_status(
				libinput_device_config_scroll_set_natural_scroll_enabled(
					libinput_device, ic->natural_scroll));
	}
	if (ic->pointer_accel != FLT_MIN) {
		sway_log(SWAY_DEBUG, "libinput_config_pointer(%s) accel_set_speed(%f)",
			ic->identifier, ic->pointer_accel);
		log_libinput_config_status(libinput_device_config_accel_set_speed(
					libinput_device, ic->pointer_accel));
	}
	if (ic->scroll_button != INT_MIN) {
		sway_log(SWAY_DEBUG, "libinput_config_pointer(%s) scroll_set_button(%d)",
			ic->identifier, ic->scroll_button);
		log_libinput_config_status(libinput_device_config_scroll_set_button(
					libinput_device, ic->scroll_button));
	}
	if (ic->scroll_method != INT_MIN) {
		sway_log(SWAY_DEBUG, "libinput_config_pointer(%s) scroll_set_method(%d)",
			ic->identifier, ic->scroll_method);
		log_libinput_config_status(libinput_device_config_scroll_set_method(
					libinput_device, ic->scroll_method));
	}
	if (ic->send_events != INT_MIN) {
		sway_log(SWAY_DEBUG, "libinput_config_pointer(%s) send_events_set_mode(%d)",
			ic->identifier, ic->send_events);
		log_libinput_config_status(libinput_device_config_send_events_set_mode(
					libinput_device, ic->send_events));
	}
	if (ic->tap != INT_MIN) {
		sway_log(SWAY_DEBUG, "libinput_config_pointer(%s) tap_set_enabled(%d)",
			ic->identifier, ic->tap);
		log_libinput_config_status(libinput_device_config_tap_set_enabled(
					libinput_device, ic->tap));
	}
	if (ic->tap_button_map != INT_MIN) {
		sway_log(SWAY_DEBUG, "libinput_config_pointer(%s) tap_set_button_map(%d)",
			ic->identifier, ic->tap_button_map);
		log_libinput_config_status(libinput_device_config_tap_set_button_map(
					libinput_device, ic->tap_button_map));
	}
}