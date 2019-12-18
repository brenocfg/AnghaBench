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

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  libinput_device_config_accel_get_default_profile (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_accel_get_default_speed (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_click_get_default_method (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_dwt_get_default_enabled (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_left_handed_get_default (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_middle_emulation_get_default_enabled (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_scroll_get_default_button (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_scroll_get_default_method (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_scroll_get_default_natural_scroll_enabled (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_send_events_get_default_mode (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_tap_get_default_button_map (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_tap_get_default_drag_enabled (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_tap_get_default_drag_lock_enabled (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_tap_get_default_enabled (struct libinput_device*) ; 
 int set_accel_profile (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int set_accel_speed (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int set_click_method (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int set_dwt (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int set_left_handed (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int set_middle_emulation (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int set_natural_scroll (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int set_scroll_button (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int set_scroll_method (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int set_send_events (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int set_tap (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int set_tap_button_map (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int set_tap_drag (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int set_tap_drag_lock (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static bool reset_libinput_pointer(struct libinput_device *device,
		const char *device_id) {
	sway_log(SWAY_DEBUG, "reset_libinput_pointer(%s)", device_id);
	bool changed = false;
	changed |= set_send_events(device,
		libinput_device_config_send_events_get_default_mode(device));
	changed |= set_tap(device,
		libinput_device_config_tap_get_default_enabled(device));
	changed |= set_tap_button_map(device,
		libinput_device_config_tap_get_default_button_map(device));
	changed |= set_tap_drag(device,
		libinput_device_config_tap_get_default_drag_enabled(device));
	changed |= set_tap_drag_lock(device,
		libinput_device_config_tap_get_default_drag_lock_enabled(device));
	changed |= set_accel_speed(device,
		libinput_device_config_accel_get_default_speed(device));
	changed |= set_accel_profile(device,
		libinput_device_config_accel_get_default_profile(device));
	changed |= set_natural_scroll(device,
		libinput_device_config_scroll_get_default_natural_scroll_enabled(
		device));
	changed |= set_left_handed(device,
		libinput_device_config_left_handed_get_default(device));
	changed |= set_click_method(device,
		libinput_device_config_click_get_default_method(device));
	changed |= set_middle_emulation(device,
		libinput_device_config_middle_emulation_get_default_enabled(device));
	changed |= set_scroll_method(device,
		libinput_device_config_scroll_get_default_method(device));
	changed |= set_scroll_button(device,
		libinput_device_config_scroll_get_default_button(device));
	changed |= set_dwt(device,
		libinput_device_config_dwt_get_default_enabled(device));
	return changed;
}