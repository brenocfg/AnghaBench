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
 int nelem (int /*<<< orphan*/ *) ; 
 int* single_code_list ; 
 int /*<<< orphan*/ * single_name_list ; 
 int strcmp (char const*,int /*<<< orphan*/ ) ; 

int
fz_unicode_from_glyph_name_strict(const char *name)
{
	int l = 0;
	int r = nelem(single_name_list) - 1;

	while (l <= r)
	{
		int m = (l + r) >> 1;
		int c = strcmp(name, single_name_list[m]);
		if (c < 0)
			r = m - 1;
		else if (c > 0)
			l = m + 1;
		else
			return single_code_list[m];
	}
	return 0;
}