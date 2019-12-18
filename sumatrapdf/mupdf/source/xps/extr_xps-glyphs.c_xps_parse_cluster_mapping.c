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
xps_parse_cluster_mapping(char *s, int *code_count, int *glyph_count)
{
	if (*s == '(')
		s = xps_parse_digits(s + 1, code_count);
	if (*s == ':')
		s = xps_parse_digits(s + 1, glyph_count);
	if (*s == ')')
		s ++;
	return s;
}