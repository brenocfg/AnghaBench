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
typedef  int uint32_t ;
struct wlr_input_device {int dummy; } ;
struct sway_input_device {int /*<<< orphan*/  identifier; struct wlr_input_device* wlr_device; } ;
struct libinput_device {int dummy; } ;
typedef  enum libinput_config_tap_state { ____Placeholder_libinput_config_tap_state } libinput_config_tap_state ;
typedef  enum libinput_config_tap_button_map { ____Placeholder_libinput_config_tap_button_map } libinput_config_tap_button_map ;
typedef  enum libinput_config_scroll_method { ____Placeholder_libinput_config_scroll_method } libinput_config_scroll_method ;
typedef  enum libinput_config_middle_emulation_state { ____Placeholder_libinput_config_middle_emulation_state } libinput_config_middle_emulation_state ;
typedef  enum libinput_config_dwt_state { ____Placeholder_libinput_config_dwt_state } libinput_config_dwt_state ;
typedef  enum libinput_config_drag_state { ____Placeholder_libinput_config_drag_state } libinput_config_drag_state ;
typedef  enum libinput_config_drag_lock_state { ____Placeholder_libinput_config_drag_lock_state } libinput_config_drag_lock_state ;
typedef  enum libinput_config_click_method { ____Placeholder_libinput_config_click_method } libinput_config_click_method ;
typedef  enum libinput_config_accel_profile { ____Placeholder_libinput_config_accel_profile } libinput_config_accel_profile ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int libinput_device_config_accel_get_default_profile (struct libinput_device*) ; 
 double libinput_device_config_accel_get_default_speed (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_accel_set_profile (struct libinput_device*,int) ; 
 int /*<<< orphan*/  libinput_device_config_accel_set_speed (struct libinput_device*,double) ; 
 int libinput_device_config_click_get_default_method (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_click_set_method (struct libinput_device*,int) ; 
 int libinput_device_config_dwt_get_default_enabled (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_dwt_set_enabled (struct libinput_device*,int) ; 
 int libinput_device_config_left_handed_get_default (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_left_handed_set (struct libinput_device*,int) ; 
 int libinput_device_config_middle_emulation_get_default_enabled (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_middle_emulation_set_enabled (struct libinput_device*,int) ; 
 int libinput_device_config_scroll_get_default_button (struct libinput_device*) ; 
 int libinput_device_config_scroll_get_default_method (struct libinput_device*) ; 
 int libinput_device_config_scroll_get_default_natural_scroll_enabled (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_scroll_set_button (struct libinput_device*,int) ; 
 int /*<<< orphan*/  libinput_device_config_scroll_set_method (struct libinput_device*,int) ; 
 int /*<<< orphan*/  libinput_device_config_scroll_set_natural_scroll_enabled (struct libinput_device*,int) ; 
 int libinput_device_config_send_events_get_default_mode (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_send_events_set_mode (struct libinput_device*,int) ; 
 int libinput_device_config_tap_get_button_map (struct libinput_device*) ; 
 int libinput_device_config_tap_get_default_drag_enabled (struct libinput_device*) ; 
 int libinput_device_config_tap_get_default_drag_lock_enabled (struct libinput_device*) ; 
 int libinput_device_config_tap_get_default_enabled (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_tap_set_button_map (struct libinput_device*,int) ; 
 int /*<<< orphan*/  libinput_device_config_tap_set_drag_enabled (struct libinput_device*,int) ; 
 int /*<<< orphan*/  libinput_device_config_tap_set_drag_lock_enabled (struct libinput_device*,int) ; 
 int /*<<< orphan*/  libinput_device_config_tap_set_enabled (struct libinput_device*,int) ; 
 int /*<<< orphan*/  log_libinput_config_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlr_input_device_is_libinput (struct wlr_input_device*) ; 
 struct libinput_device* wlr_libinput_get_device_handle (struct wlr_input_device*) ; 

__attribute__((used)) static void input_manager_libinput_reset_pointer(
		struct sway_input_device *input_device) {
	struct wlr_input_device *wlr_device = input_device->wlr_device;

	if (!wlr_input_device_is_libinput(wlr_device)) {
		return;
	}

	struct libinput_device *libinput_device =
		wlr_libinput_get_device_handle(wlr_device);

	enum libinput_config_accel_profile accel_profile =
		libinput_device_config_accel_get_default_profile(libinput_device);
	sway_log(SWAY_DEBUG, "libinput_reset_pointer(%s) accel_set_profile(%d)",
			input_device->identifier, accel_profile);
	log_libinput_config_status(libinput_device_config_accel_set_profile(
				libinput_device, accel_profile));

	enum libinput_config_click_method click_method =
		libinput_device_config_click_get_default_method(libinput_device);
	sway_log(SWAY_DEBUG, "libinput_reset_pointer(%s) click_set_method(%d)",
		input_device->identifier, click_method);
	log_libinput_config_status(libinput_device_config_click_set_method(
				libinput_device, click_method));

	enum libinput_config_drag_state drag =
		libinput_device_config_tap_get_default_drag_enabled(libinput_device);
	sway_log(SWAY_DEBUG, "libinput_reset_pointer(%s) tap_set_drag_enabled(%d)",
			input_device->identifier, drag);
	log_libinput_config_status(libinput_device_config_tap_set_drag_enabled(
				libinput_device, drag));

	enum libinput_config_drag_lock_state drag_lock =
		libinput_device_config_tap_get_default_drag_lock_enabled(
				libinput_device);
	sway_log(SWAY_DEBUG,
			"libinput_reset_pointer(%s) tap_set_drag_lock_enabled(%d)",
			input_device->identifier, drag_lock);
	log_libinput_config_status(
			libinput_device_config_tap_set_drag_lock_enabled(
				libinput_device, drag_lock));

	enum libinput_config_dwt_state dwt =
		libinput_device_config_dwt_get_default_enabled(libinput_device);
	sway_log(SWAY_DEBUG, "libinput_reset_pointer(%s) dwt_set_enabled(%d)",
		input_device->identifier, dwt);
	log_libinput_config_status(libinput_device_config_dwt_set_enabled(
				libinput_device, dwt));

	int left_handed =
		libinput_device_config_left_handed_get_default(libinput_device);
	sway_log(SWAY_DEBUG,
		"libinput_reset_pointer(%s) left_handed_set_enabled(%d)",
		input_device->identifier, left_handed);
	log_libinput_config_status(libinput_device_config_left_handed_set(
				libinput_device, left_handed));

	enum libinput_config_middle_emulation_state middle_emulation =
		libinput_device_config_middle_emulation_get_default_enabled(
				libinput_device);
	sway_log(SWAY_DEBUG,
		"libinput_reset_pointer(%s) middle_emulation_set_enabled(%d)",
		input_device->identifier, middle_emulation);
	log_libinput_config_status(
			libinput_device_config_middle_emulation_set_enabled(
				libinput_device, middle_emulation));

	int natural_scroll =
		libinput_device_config_scroll_get_default_natural_scroll_enabled(
				libinput_device);
	sway_log(SWAY_DEBUG,
		"libinput_reset_pointer(%s) natural_scroll_set_enabled(%d)",
		input_device->identifier, natural_scroll);
	log_libinput_config_status(
			libinput_device_config_scroll_set_natural_scroll_enabled(
				libinput_device, natural_scroll));

	double pointer_accel =
		libinput_device_config_accel_get_default_speed(libinput_device);
	sway_log(SWAY_DEBUG, "libinput_reset_pointer(%s) accel_set_speed(%f)",
		input_device->identifier, pointer_accel);
	log_libinput_config_status(libinput_device_config_accel_set_speed(
				libinput_device, pointer_accel));

	uint32_t scroll_button =
		libinput_device_config_scroll_get_default_button(libinput_device);
	sway_log(SWAY_DEBUG, "libinput_reset_pointer(%s) scroll_set_button(%d)",
		input_device->identifier, scroll_button);
	log_libinput_config_status(libinput_device_config_scroll_set_button(
				libinput_device, scroll_button));

	enum libinput_config_scroll_method scroll_method =
		libinput_device_config_scroll_get_default_method(libinput_device);
	sway_log(SWAY_DEBUG, "libinput_reset_pointer(%s) scroll_set_method(%d)",
		input_device->identifier, scroll_method);
	log_libinput_config_status(libinput_device_config_scroll_set_method(
				libinput_device, scroll_method));

	uint32_t send_events =
		libinput_device_config_send_events_get_default_mode(libinput_device);
	sway_log(SWAY_DEBUG, "libinput_reset_pointer(%s) send_events_set_mode(%d)",
		input_device->identifier, send_events);
	log_libinput_config_status(libinput_device_config_send_events_set_mode(
				libinput_device, send_events));

	enum libinput_config_tap_state tap =
		libinput_device_config_tap_get_default_enabled(libinput_device);
	sway_log(SWAY_DEBUG, "libinput_reset_pointer(%s) tap_set_enabled(%d)",
		input_device->identifier, tap);
	log_libinput_config_status(libinput_device_config_tap_set_enabled(
				libinput_device, tap));

	enum libinput_config_tap_button_map tap_button_map =
		libinput_device_config_tap_get_button_map(libinput_device);
	sway_log(SWAY_DEBUG, "libinput_reset_pointer(%s) tap_set_button_map(%d)",
		input_device->identifier, tap_button_map);
	log_libinput_config_status(libinput_device_config_tap_set_button_map(
				libinput_device, tap_button_map));
}