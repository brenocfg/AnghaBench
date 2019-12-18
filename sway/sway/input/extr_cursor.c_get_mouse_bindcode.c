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

/* Variables and functions */
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  EV_KEY ; 
 scalar_t__ errno ; 
 char* libevdev_event_code_get_name (int /*<<< orphan*/ ,int) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,char const*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 
 int strtol (char const*,char**,int) ; 

uint32_t get_mouse_bindcode(const char *name, char **error) {
	// Validate event code
	errno = 0;
	char *endptr;
	int code = strtol(name, &endptr, 10);
	if (endptr == name && code <= 0) {
		*error = strdup("Button event code must be a positive integer.");
		return 0;
	} else if (errno == ERANGE) {
		*error = strdup("Button event code out of range.");
		return 0;
	}
	const char *event = libevdev_event_code_get_name(EV_KEY, code);
	if (!event || strncmp(event, "BTN_", strlen("BTN_")) != 0) {
		size_t len = snprintf(NULL, 0, "Event code %d (%s) is not a button",
				code, event) + 1;
		*error = malloc(len);
		if (*error) {
			snprintf(*error, len, "Event code %d (%s) is not a button",
					code, event);
		}
		return 0;
	}
	return code;
}