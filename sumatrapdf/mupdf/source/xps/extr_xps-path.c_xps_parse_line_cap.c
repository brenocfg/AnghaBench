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
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int
xps_parse_line_cap(char *attr)
{
	if (attr)
	{
		if (!strcmp(attr, "Flat")) return 0;
		if (!strcmp(attr, "Round")) return 1;
		if (!strcmp(attr, "Square")) return 2;
		if (!strcmp(attr, "Triangle")) return 3;
	}
	return 0;
}