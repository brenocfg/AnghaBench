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

const char *
svg_lex_number(float *fp, const char *ss)
{
	const char *s = ss;
	if (*s == '-')
		++s;
	while (*s >= '0' && *s <= '9')
		++s;
	if (*s == '.') {
		++s;
		while (*s >= '0' && *s <= '9')
			++s;
	}
	if (*s == 'e' || *s == 'E') {
		++s;
		if (*s == '+' || *s == '-')
			++s;
		while (*s >= '0' && *s <= '9')
			++s;
	}
	*fp = fz_atof(ss);
	return s;
}