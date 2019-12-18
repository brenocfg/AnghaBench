#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int u; char const* n; } ;

/* Variables and functions */
 TYPE_1__* glyph_name_from_unicode_sc ; 
 int nelem (TYPE_1__*) ; 

const char *
fz_glyph_name_from_unicode_sc(int u)
{
	int l = 0;
	int r = nelem(glyph_name_from_unicode_sc) / 2 - 1;
	while (l <= r)
	{
		int m = (l + r) >> 1;
		if (u < glyph_name_from_unicode_sc[m].u)
			r = m - 1;
		else if (u > glyph_name_from_unicode_sc[m].u)
			l = m + 1;
		else
			return glyph_name_from_unicode_sc[m].n;
	}
	return NULL;
}