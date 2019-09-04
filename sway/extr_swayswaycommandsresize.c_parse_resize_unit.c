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
typedef  enum resize_unit { ____Placeholder_resize_unit } resize_unit ;

/* Variables and functions */
 int RESIZE_UNIT_DEFAULT ; 
 int RESIZE_UNIT_INVALID ; 
 int RESIZE_UNIT_PPT ; 
 int RESIZE_UNIT_PX ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static enum resize_unit parse_resize_unit(const char *unit) {
	if (strcasecmp(unit, "px") == 0) {
		return RESIZE_UNIT_PX;
	}
	if (strcasecmp(unit, "ppt") == 0) {
		return RESIZE_UNIT_PPT;
	}
	if (strcasecmp(unit, "default") == 0) {
		return RESIZE_UNIT_DEFAULT;
	}
	return RESIZE_UNIT_INVALID;
}