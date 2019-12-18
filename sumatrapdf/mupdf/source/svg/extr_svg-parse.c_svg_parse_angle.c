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
 float FZ_RADIAN ; 
 float fz_strtof (char const*,char**) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

float
svg_parse_angle(const char *str)
{
	char *end;
	float val;

	val = fz_strtof(str, &end);
	if (end == str)
		return 0; /* failed */

	if (!strcmp(end, "deg"))
		return val;

	if (!strcmp(end, "grad"))
		return val * 0.9f;

	if (!strcmp(end, "rad"))
		return val * FZ_RADIAN;

	return val;
}