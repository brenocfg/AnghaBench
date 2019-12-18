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
 size_t VGMASK (unsigned char,int) ; 
 int /*<<< orphan*/ * get1_tab_255p ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fz_unpack_mono_line_scaled_with_padding(unsigned char *dp, unsigned char *sp, int w, int n)
{
	int w3 = w >> 3;
	int x;

	for (x = 0; x < w3; x++)
	{
		memcpy(dp, get1_tab_255p[*sp++], 16);
		dp += 16;
	}
	x = x << 3;
	if (x < w)
		memcpy(dp, get1_tab_255p[VGMASK(*sp, w - x)], (w - x) << 1);
}