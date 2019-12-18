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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int PB_ALWAYS ; 
 int PB_LEFT ; 
 int PB_RIGHT ; 
 float fmodf (float,float) ; 

__attribute__((used)) static int layout_block_page_break(fz_context *ctx, float *yp, float page_h, float vertical, int page_break)
{
	if (page_h <= 0)
		return 0;
	if (page_break == PB_ALWAYS || page_break == PB_LEFT || page_break == PB_RIGHT)
	{
		float avail = page_h - fmodf(*yp - vertical, page_h);
		int number = (*yp + (page_h * 0.1f)) / page_h;
		if (avail > 0 && avail < page_h)
		{
			*yp += avail - vertical;
			if (page_break == PB_LEFT && (number & 1) == 0) /* right side pages are even */
				*yp += page_h;
			if (page_break == PB_RIGHT && (number & 1) == 1) /* left side pages are odd */
				*yp += page_h;
			return 1;
		}
	}
	return 0;
}