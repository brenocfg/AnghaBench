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
struct libinput_device {int dummy; } ;
struct json_object {int dummy; } ;
typedef  int /*<<< orphan*/  json_object ;

/* Variables and functions */
#define  LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE 152 
#define  LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT 151 
#define  LIBINPUT_CONFIG_ACCEL_PROFILE_NONE 150 
#define  LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS 149 
#define  LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER 148 
#define  LIBINPUT_CONFIG_CLICK_METHOD_NONE 147 
#define  LIBINPUT_CONFIG_DRAG_DISABLED 146 
#define  LIBINPUT_CONFIG_DRAG_ENABLED 145 
#define  LIBINPUT_CONFIG_DRAG_LOCK_DISABLED 144 
#define  LIBINPUT_CONFIG_DRAG_LOCK_ENABLED 143 
#define  LIBINPUT_CONFIG_DWT_DISABLED 142 
#define  LIBINPUT_CONFIG_DWT_ENABLED 141 
#define  LIBINPUT_CONFIG_MIDDLE_EMULATION_DISABLED 140 
#define  LIBINPUT_CONFIG_MIDDLE_EMULATION_ENABLED 139 
#define  LIBINPUT_CONFIG_SCROLL_2FG 138 
#define  LIBINPUT_CONFIG_SCROLL_EDGE 137 
#define  LIBINPUT_CONFIG_SCROLL_NO_SCROLL 136 
#define  LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN 135 
#define  LIBINPUT_CONFIG_SEND_EVENTS_DISABLED 134 
#define  LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE 133 
#define  LIBINPUT_CONFIG_SEND_EVENTS_ENABLED 132 
#define  LIBINPUT_CONFIG_TAP_DISABLED 131 
#define  LIBINPUT_CONFIG_TAP_ENABLED 130 
#define  LIBINPUT_CONFIG_TAP_MAP_LMR 129 
#define  LIBINPUT_CONFIG_TAP_MAP_LRM 128 
 int /*<<< orphan*/  json_object_array_add (struct json_object*,struct json_object*) ; 
 struct json_object* json_object_new_array () ; 
 struct json_object* json_object_new_double (float) ; 
 struct json_object* json_object_new_int (int) ; 
 int /*<<< orphan*/ * json_object_new_object () ; 
 struct json_object* json_object_new_string (char const*) ; 
 int /*<<< orphan*/  json_object_object_add (int /*<<< orphan*/ *,char*,struct json_object*) ; 
 int libinput_device_config_accel_get_profile (struct libinput_device*) ; 
 double libinput_device_config_accel_get_speed (struct libinput_device*) ; 
 scalar_t__ libinput_device_config_accel_is_available (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_calibration_get_matrix (struct libinput_device*,float*) ; 
 scalar_t__ libinput_device_config_calibration_has_matrix (struct libinput_device*) ; 
 int libinput_device_config_click_get_method (struct libinput_device*) ; 
 int libinput_device_config_click_get_methods (struct libinput_device*) ; 
 int libinput_device_config_dwt_get_enabled (struct libinput_device*) ; 
 scalar_t__ libinput_device_config_dwt_is_available (struct libinput_device*) ; 
 scalar_t__ libinput_device_config_left_handed_get (struct libinput_device*) ; 
 scalar_t__ libinput_device_config_left_handed_is_available (struct libinput_device*) ; 
 int libinput_device_config_middle_emulation_get_enabled (struct libinput_device*) ; 
 scalar_t__ libinput_device_config_middle_emulation_is_available (struct libinput_device*) ; 
 int libinput_device_config_scroll_get_button (struct libinput_device*) ; 
 int libinput_device_config_scroll_get_method (struct libinput_device*) ; 
 int libinput_device_config_scroll_get_methods (struct libinput_device*) ; 
 scalar_t__ libinput_device_config_scroll_get_natural_scroll_enabled (struct libinput_device*) ; 
 scalar_t__ libinput_device_config_scroll_has_natural_scroll (struct libinput_device*) ; 
 int libinput_device_config_send_events_get_mode (struct libinput_device*) ; 
 int libinput_device_config_tap_get_button_map (struct libinput_device*) ; 
 int libinput_device_config_tap_get_drag_enabled (struct libinput_device*) ; 
 int libinput_device_config_tap_get_drag_lock_enabled (struct libinput_device*) ; 
 int libinput_device_config_tap_get_enabled (struct libinput_device*) ; 
 scalar_t__ libinput_device_config_tap_get_finger_count (struct libinput_device*) ; 

__attribute__((used)) static json_object *describe_libinput_device(struct libinput_device *device) {
	json_object *object = json_object_new_object();

	const char *events = "unknown";
	switch (libinput_device_config_send_events_get_mode(device)) {
	case LIBINPUT_CONFIG_SEND_EVENTS_ENABLED:
		events = "enabled";
		break;
	case LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE:
		events = "disabled_on_external_mouse";
		break;
	case LIBINPUT_CONFIG_SEND_EVENTS_DISABLED:
		events = "disabled";
		break;
	}
	json_object_object_add(object, "send_events",
			json_object_new_string(events));

	if (libinput_device_config_tap_get_finger_count(device) > 0) {
		const char *tap = "unknown";
		switch (libinput_device_config_tap_get_enabled(device)) {
		case LIBINPUT_CONFIG_TAP_ENABLED:
			tap = "enabled";
			break;
		case LIBINPUT_CONFIG_TAP_DISABLED:
			tap = "disabled";
			break;
		}
		json_object_object_add(object, "tap", json_object_new_string(tap));

		const char *button_map = "unknown";
		switch (libinput_device_config_tap_get_button_map(device)) {
		case LIBINPUT_CONFIG_TAP_MAP_LRM:
			button_map = "lrm";
			break;
		case LIBINPUT_CONFIG_TAP_MAP_LMR:
			button_map = "lmr";
			break;
		}
		json_object_object_add(object, "tap_button_map",
				json_object_new_string(button_map));

		const char* drag = "unknown";
		switch (libinput_device_config_tap_get_drag_enabled(device)) {
		case LIBINPUT_CONFIG_DRAG_ENABLED:
			drag = "enabled";
			break;
		case LIBINPUT_CONFIG_DRAG_DISABLED:
			drag = "disabled";
			break;
		}
		json_object_object_add(object, "tap_drag",
				json_object_new_string(drag));

		const char *drag_lock = "unknown";
		switch (libinput_device_config_tap_get_drag_lock_enabled(device)) {
		case LIBINPUT_CONFIG_DRAG_LOCK_ENABLED:
			drag_lock = "enabled";
			break;
		case LIBINPUT_CONFIG_DRAG_LOCK_DISABLED:
			drag_lock = "disabled";
			break;
		}
		json_object_object_add(object, "tap_drag_lock",
				json_object_new_string(drag_lock));
	}

	if (libinput_device_config_accel_is_available(device)) {
		double accel = libinput_device_config_accel_get_speed(device);
		json_object_object_add(object, "accel_speed",
				json_object_new_double(accel));

		const char *accel_profile = "unknown";
		switch (libinput_device_config_accel_get_profile(device)) {
		case LIBINPUT_CONFIG_ACCEL_PROFILE_NONE:
			accel_profile = "none";
			break;
		case LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT:
			accel_profile = "flat";
			break;
		case LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE:
			accel_profile = "adaptive";
			break;
		}
		json_object_object_add(object, "accel_profile",
				json_object_new_string(accel_profile));
	}

	if (libinput_device_config_scroll_has_natural_scroll(device)) {
		const char *natural_scroll = "disabled";
		if (libinput_device_config_scroll_get_natural_scroll_enabled(device)) {
			natural_scroll = "enabled";
		}
		json_object_object_add(object, "natural_scroll",
				json_object_new_string(natural_scroll));
	}

	if (libinput_device_config_left_handed_is_available(device)) {
		const char *left_handed = "disabled";
		if (libinput_device_config_left_handed_get(device) != 0) {
			left_handed = "enabled";
		}
		json_object_object_add(object, "left_handed",
				json_object_new_string(left_handed));
	}

	uint32_t click_methods = libinput_device_config_click_get_methods(device);
	if ((click_methods & ~LIBINPUT_CONFIG_CLICK_METHOD_NONE) != 0) {
		const char *click_method = "unknown";
		switch (libinput_device_config_click_get_method(device)) {
		case LIBINPUT_CONFIG_CLICK_METHOD_NONE:
			click_method = "none";
			break;
		case LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS:
			click_method = "button_areas";
			break;
		case LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER:
			click_method = "clickfinger";
			break;
		}
		json_object_object_add(object, "click_method",
				json_object_new_string(click_method));
	}

	if (libinput_device_config_middle_emulation_is_available(device)) {
		const char *middle_emulation = "unknown";
		switch (libinput_device_config_middle_emulation_get_enabled(device)) {
		case LIBINPUT_CONFIG_MIDDLE_EMULATION_ENABLED:
			middle_emulation = "enabled";
			break;
		case LIBINPUT_CONFIG_MIDDLE_EMULATION_DISABLED:
			middle_emulation = "disabled";
			break;
		}
		json_object_object_add(object, "middle_emulation",
				json_object_new_string(middle_emulation));
	}

	uint32_t scroll_methods = libinput_device_config_scroll_get_methods(device);
	if ((scroll_methods & ~LIBINPUT_CONFIG_SCROLL_NO_SCROLL) != 0) {
		const char *scroll_method = "unknown";
		switch (libinput_device_config_scroll_get_method(device)) {
		case LIBINPUT_CONFIG_SCROLL_NO_SCROLL:
			scroll_method = "none";
			break;
		case LIBINPUT_CONFIG_SCROLL_2FG:
			scroll_method = "two_finger";
			break;
		case LIBINPUT_CONFIG_SCROLL_EDGE:
			scroll_method = "edge";
			break;
		case LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN:
			scroll_method = "on_button_down";
			break;
		}
		json_object_object_add(object, "scroll_method",
				json_object_new_string(scroll_method));

		if ((scroll_methods & LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN) != 0) {
			uint32_t button = libinput_device_config_scroll_get_button(device);
			json_object_object_add(object, "scroll_button",
					json_object_new_int(button));
		}
	}

	if (libinput_device_config_dwt_is_available(device)) {
		const char *dwt = "unknown";
		switch (libinput_device_config_dwt_get_enabled(device)) {
		case LIBINPUT_CONFIG_DWT_ENABLED:
			dwt = "enabled";
			break;
		case LIBINPUT_CONFIG_DWT_DISABLED:
			dwt = "disabled";
			break;
		}
		json_object_object_add(object, "dwt", json_object_new_string(dwt));
	}

	if (libinput_device_config_calibration_has_matrix(device)) {
		float matrix[6];
		libinput_device_config_calibration_get_matrix(device, matrix);
		struct json_object* array = json_object_new_array();
		struct json_object* x;
		for (int i = 0; i < 6; i++) {
			x = json_object_new_double(matrix[i]);
			json_object_array_add(array, x);
		}
		json_object_object_add(object, "calibration_matrix", array);
	}

	return object;
}