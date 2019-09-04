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
typedef  int const uint32_t ;

/* Variables and functions */
#define  BTN_EXTRA 136 
#define  BTN_LEFT 135 
#define  BTN_MIDDLE 134 
#define  BTN_RIGHT 133 
#define  BTN_SIDE 132 
 int /*<<< orphan*/  EV_KEY ; 
#define  SWAY_SCROLL_DOWN 131 
#define  SWAY_SCROLL_LEFT 130 
#define  SWAY_SCROLL_RIGHT 129 
#define  SWAY_SCROLL_UP 128 
 int libevdev_event_code_from_name (int /*<<< orphan*/ ,char const*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*) ; 
 char* strdup (char*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char*,size_t) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 

uint32_t get_mouse_bindsym(const char *name, char **error) {
	if (strncasecmp(name, "button", strlen("button")) == 0) {
		// Map to x11 mouse buttons
		int number = name[strlen("button")] - '0';
		if (number < 1 || number > 9 || strlen(name) > strlen("button0")) {
			*error = strdup("Only buttons 1-9 are supported. For other mouse "
					"buttons, use the name of the event code.");
			return 0;
		}
		static const uint32_t buttons[] = {BTN_LEFT, BTN_MIDDLE, BTN_RIGHT,
			SWAY_SCROLL_UP, SWAY_SCROLL_DOWN, SWAY_SCROLL_LEFT,
			SWAY_SCROLL_RIGHT, BTN_SIDE, BTN_EXTRA};
		return buttons[number - 1];
	} else if (strncmp(name, "BTN_", strlen("BTN_")) == 0) {
		// Get event code from name
		int code = libevdev_event_code_from_name(EV_KEY, name);
		if (code == -1) {
			size_t len = snprintf(NULL, 0, "Unknown event %s", name) + 1;
			*error = malloc(len);
			if (*error) {
				snprintf(*error, len, "Unknown event %s", name);
			}
			return 0;
		}
		return code;
	}
	return 0;
}