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

/* Variables and functions */
 scalar_t__ strcasecmp (char const*,char*) ; 

bool parse_boolean(const char *boolean, bool current) {
	if (strcasecmp(boolean, "1") == 0
			|| strcasecmp(boolean, "yes") == 0
			|| strcasecmp(boolean, "on") == 0
			|| strcasecmp(boolean, "true") == 0
			|| strcasecmp(boolean, "enable") == 0
			|| strcasecmp(boolean, "enabled") == 0
			|| strcasecmp(boolean, "active") == 0) {
		return true;
	} else if (strcasecmp(boolean, "toggle") == 0) {
		return !current;
	}
	// All other values are false to match i3
	return false;
}