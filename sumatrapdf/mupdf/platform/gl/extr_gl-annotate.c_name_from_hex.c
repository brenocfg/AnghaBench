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
 char const** color_names ; 
 unsigned int* color_values ; 
 int /*<<< orphan*/  fz_snprintf (char*,int,char*,unsigned int) ; 
 scalar_t__ nelem (char const**) ; 

__attribute__((used)) static const char *name_from_hex(unsigned int hex)
{
	static char buf[10];
	int i;
	for (i = 0; i < (int)nelem(color_names); ++i)
		if (color_values[i] == hex)
			return color_names[i];
	fz_snprintf(buf, sizeof buf, "#%06x", hex & 0xffffff);
	return buf;
}