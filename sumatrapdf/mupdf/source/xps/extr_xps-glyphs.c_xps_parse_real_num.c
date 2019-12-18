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
 float fz_strtof (char*,char**) ; 

__attribute__((used)) static char *
xps_parse_real_num(char *s, float *number, int *override)
{
	char *tail;
	float v;
	v = fz_strtof(s, &tail);
	*override = tail != s;
	if (*override)
		*number = v;
	return tail;
}