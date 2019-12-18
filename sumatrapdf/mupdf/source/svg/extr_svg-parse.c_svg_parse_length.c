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
 float fz_strtof (char const*,char**) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

float
svg_parse_length(const char *str, float percent, float font_size)
{
	char *end;
	float val;

	val = fz_strtof(str, &end);
	if (end == str)
		return 0; /* failed */

	if (!strcmp(end, "px")) return val;

	if (!strcmp(end, "pt")) return val * 1.0f;
	if (!strcmp(end, "pc")) return val * 12.0f;
	if (!strcmp(end, "mm")) return val * 2.83464567f;
	if (!strcmp(end, "cm")) return val * 28.3464567f;
	if (!strcmp(end, "in")) return val * 72.0f;

	if (!strcmp(end, "em")) return val * font_size;
	if (!strcmp(end, "ex")) return val * font_size * 0.5f;

	if (!strcmp(end, "%"))
		return val * percent * 0.01f;

	if (end[0] == 0)
		return val;

	return 0;
}