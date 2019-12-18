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
struct TYPE_3__ {unsigned char* samples; int h; int stride; int w; int n; } ;
typedef  TYPE_1__ fz_pixmap ;

/* Variables and functions */

__attribute__((used)) static void
fz_mask_color_key(fz_pixmap *pix, int n, const int *colorkey)
{
	unsigned char *p = pix->samples;
	int w;
	int k, t;
	int h = pix->h;
	int stride = pix->stride - pix->w * pix->n;
	if (pix->w == 0)
		return;
	while (h--)
	{
		w = pix->w;
		do
		{
			t = 1;
			for (k = 0; k < n; k++)
				if (p[k] < colorkey[k * 2] || p[k] > colorkey[k * 2 + 1])
					t = 0;
			if (t)
				for (k = 0; k < pix->n; k++)
					p[k] = 0;
			p += pix->n;
		}
		while (--w);
		p += stride;
	}
}