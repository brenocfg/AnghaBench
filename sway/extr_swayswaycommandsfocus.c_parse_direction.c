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
typedef  enum wlr_direction { ____Placeholder_wlr_direction } wlr_direction ;

/* Variables and functions */
 int WLR_DIRECTION_DOWN ; 
 int WLR_DIRECTION_LEFT ; 
 int WLR_DIRECTION_RIGHT ; 
 int WLR_DIRECTION_UP ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static bool parse_direction(const char *name,
		enum wlr_direction *out) {
	if (strcasecmp(name, "left") == 0) {
		*out = WLR_DIRECTION_LEFT;
	} else if (strcasecmp(name, "right") == 0) {
		*out = WLR_DIRECTION_RIGHT;
	} else if (strcasecmp(name, "up") == 0) {
		*out = WLR_DIRECTION_UP;
	} else if (strcasecmp(name, "down") == 0) {
		*out = WLR_DIRECTION_DOWN;
	} else {
		return false;
	}

	return true;
}