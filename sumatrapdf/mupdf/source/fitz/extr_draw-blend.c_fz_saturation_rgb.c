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
 void* fz_clampi (int,int /*<<< orphan*/ ,int) ; 
 int fz_maxi (int,int) ; 
 int fz_mini (int,int) ; 

__attribute__((used)) static void
fz_saturation_rgb(unsigned char *rd, unsigned char *gd, unsigned char *bd, int rb, int gb, int bb, int rs, int gs, int bs)
{
	int minb, maxb;
	int mins, maxs;
	int y;
	int scale;
	int r, g, b;

	minb = fz_mini(rb, fz_mini(gb, bb));
	maxb = fz_maxi(rb, fz_maxi(gb, bb));
	if (minb == maxb)
	{
		/* backdrop has zero saturation, avoid divide by 0 */
		gb = fz_clampi(gb, 0, 255);
		*rd = gb;
		*gd = gb;
		*bd = gb;
		return;
	}

	mins = fz_mini(rs, fz_mini(gs, bs));
	maxs = fz_maxi(rs, fz_maxi(gs, bs));

	scale = ((maxs - mins) << 16) / (maxb - minb);
	y = (rb * 77 + gb * 151 + bb * 28 + 0x80) >> 8;
	r = y + ((((rb - y) * scale) + 0x8000) >> 16);
	g = y + ((((gb - y) * scale) + 0x8000) >> 16);
	b = y + ((((bb - y) * scale) + 0x8000) >> 16);

	if ((r | g | b) & 0x100)
	{
		int scalemin, scalemax;
		int min, max;

		min = fz_mini(r, fz_mini(g, b));
		max = fz_maxi(r, fz_maxi(g, b));

		if (min < 0)
			scalemin = (y << 16) / (y - min);
		else
			scalemin = 0x10000;

		if (max > 255)
			scalemax = ((255 - y) << 16) / (max - y);
		else
			scalemax = 0x10000;

		scale = fz_mini(scalemin, scalemax);
		r = y + (((r - y) * scale + 0x8000) >> 16);
		g = y + (((g - y) * scale + 0x8000) >> 16);
		b = y + (((b - y) * scale + 0x8000) >> 16);
	}

	*rd = fz_clampi(r, 0, 255);
	*gd = fz_clampi(g, 0, 255);
	*bd = fz_clampi(b, 0, 255);
}