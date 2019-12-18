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
 char* xps_parse_digits (char*,int*) ; 

__attribute__((used)) static char *
xps_parse_glyph_index(char *s, int *glyph_index)
{
	if (*s >= '0' && *s <= '9')
		s = xps_parse_digits(s, glyph_index);
	return s;
}