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
 float NAN ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 scalar_t__ errno ; 
 float strtof (char const*,char**) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char const*) ; 

float parse_float(const char *value) {
	errno = 0;
	char *end;
	float flt = strtof(value, &end);
	if (*end || errno) {
		sway_log(SWAY_DEBUG, "Invalid float value '%s', defaulting to NAN", value);
		return NAN;
	}
	return flt;
}