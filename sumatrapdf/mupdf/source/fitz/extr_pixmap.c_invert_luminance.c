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
 int FZ_COLORSPACE_RGB ; 

__attribute__((used)) static inline void invert_luminance(int type, unsigned char *s)
{
	int r, g, b, y, u, v, c, d, e;

	/* Convert to YUV */
	if (type == FZ_COLORSPACE_RGB)
	{
		r = s[0];
		g = s[1];
		b = s[2];
	}
	else
	{
		r = s[2];
		g = s[1];
		b = s[0];
	}

	y = ((66 * r + 129 * g + 25 * b + 128) >> 8) + 16;
	u = ((-38 * r - 74 * g + 112 * b + 128) >> 8) + 128;
	v = ((112 * r - 94 * g - 18 * b + 128) >> 8) + 128;

	/* Invert luminance */
	y = 255 - y;

	/* Convert to RGB */
	c = y - 16;
	d = u - 128;
	e = v - 128;
	r = (298 * c + 409 * e + 128) >> 8;
	g = (298 * c - 100 * d - 208 * e + 128) >> 8;
	b = (298 * c + 516 * d + 128) >> 8;

	if (type == FZ_COLORSPACE_RGB)
	{
		s[0] = r > 255 ? 255 : r < 0 ? 0 : r;
		s[1] = g > 255 ? 255 : g < 0 ? 0 : g;
		s[2] = b > 255 ? 255 : b < 0 ? 0 : b;
	}
	else
	{
		s[2] = r > 255 ? 255 : r < 0 ? 0 : r;
		s[1] = g > 255 ? 255 : g < 0 ? 0 : g;
		s[0] = b > 255 ? 255 : b < 0 ? 0 : b;
	}
}