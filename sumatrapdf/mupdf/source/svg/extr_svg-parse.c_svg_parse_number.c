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
 float fz_atof (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

float
svg_parse_number(const char *str, float min, float max, float inherit)
{
	float x;
	if (!strcmp(str, "inherit"))
		return inherit;
	x = fz_atof(str);
	if (x < min) return min;
	if (x > max) return max;
	return x;
}