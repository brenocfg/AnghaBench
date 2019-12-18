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
typedef  int WCHAR ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int* Tbl ; 

WCHAR ff_convert (	/* Converted character, Returns zero on error */
	WCHAR	chr,	/* Character code to be converted */
	UINT	dir		/* 0: Unicode to OEM code, 1: OEM code to Unicode */
)
{
	WCHAR c;


	if (chr < 0x80) {	/* ASCII */
		c = chr;

	} else {
		if (dir) {		/* OEM code to Unicode */
			c = (chr >= 0x100) ? 0 : Tbl[chr - 0x80];

		} else {		/* Unicode to OEM code */
			for (c = 0; c < 0x80; c++) {
				if (chr == Tbl[c]) break;
			}
			c = (c + 0x80) & 0xFF;
		}
	}

	return c;
}