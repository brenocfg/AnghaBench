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
struct wlr_input_device {int vendor; int product; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int snprintf (char*,int,char const*,int,int,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strip_whitespace (char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

char *input_device_get_identifier(struct wlr_input_device *device) {
	int vendor = device->vendor;
	int product = device->product;
	char *name = strdup(device->name);
	strip_whitespace(name);

	char *p = name;
	for (; *p; ++p) {
		if (*p == ' ') {
			*p = '_';
		}
	}

	const char *fmt = "%d:%d:%s";
	int len = snprintf(NULL, 0, fmt, vendor, product, name) + 1;
	char *identifier = malloc(len);
	if (!identifier) {
		sway_log(SWAY_ERROR, "Unable to allocate unique input device name");
		return NULL;
	}

	snprintf(identifier, len, fmt, vendor, product, name);
	free(name);
	return identifier;
}