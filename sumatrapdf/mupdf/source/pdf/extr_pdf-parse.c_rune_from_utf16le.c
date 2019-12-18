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
 int FZ_REPLACEMENT_CHARACTER ; 

__attribute__((used)) static int
rune_from_utf16le(int *out, const unsigned char *s, const unsigned char *end)
{
	if (s + 2 <= end)
	{
		int a = s[1] << 8 | s[0];
		if (a >= 0xD800 && a <= 0xDFFF && s + 4 <= end)
		{
			int b = s[3] << 8 | s[2];
			*out = ((a - 0xD800) << 10) + (b - 0xDC00) + 0x10000;
			return 4;
		}
		*out = a;
		return 2;
	}
	*out = FZ_REPLACEMENT_CHARACTER;
	return 1;
}