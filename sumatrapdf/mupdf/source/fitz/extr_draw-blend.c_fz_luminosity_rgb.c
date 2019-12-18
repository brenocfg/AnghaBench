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
 unsigned char fz_clampi (int,int /*<<< orphan*/ ,int) ; 
 int fz_maxi (int,int) ; 
 int fz_mini (int,int) ; 

__attribute__((used)) static void
fz_luminosity_rgb(unsigned char *rd, unsigned char *gd, unsigned char *bd, int rb, int gb, int bb, int rs, int gs, int bs)
{
	int delta, scale;
	int r, g, b, y;

	/* 0.3f, 0.59f, 0.11f in fixed point */
	delta = ((rs - rb) * 77 + (gs - gb) * 151 + (bs - bb) * 28 + 0x80) >> 8;
	r = rb + delta;
	g = gb + delta;
	b = bb + delta;

	if ((r | g | b) & 0x100)
	{
		y = (rs * 77 + gs * 151 + bs * 28 + 0x80) >> 8;
		if (delta > 0)
		{
			int max;
			max = fz_maxi(r, fz_maxi(g, b));
			scale = (max == y ? 0 : ((255 - y) << 16) / (max - y));
		}
		else
		{
			int min;
			min = fz_mini(r, fz_mini(g, b));
			scale = (y == min ? 0 : (y << 16) / (y - min));
		}
		r = y + (((r - y) * scale + 0x8000) >> 16);
		g = y + (((g - y) * scale + 0x8000) >> 16);
		b = y + (((b - y) * scale + 0x8000) >> 16);
	}

	*rd = fz_clampi(r, 0, 255);
	*gd = fz_clampi(g, 0, 255);
	*bd = fz_clampi(b, 0, 255);
}