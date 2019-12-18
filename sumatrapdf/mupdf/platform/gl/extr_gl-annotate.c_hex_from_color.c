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
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  fz_convert_color (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ,float*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_default_color_params ; 
 int /*<<< orphan*/  fz_device_cmyk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_device_rgb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int hex_from_color(int n, float color[4])
{
	float rgb[4];
	int r, g, b;
	switch (n)
	{
	default:
		return 0;
	case 1:
		r = color[0] * 255;
		return 0xff000000 | (r<<16) | (r<<8) | r;
	case 3:
		r = color[0] * 255;
		g = color[1] * 255;
		b = color[2] * 255;
		return 0xff000000 | (r<<16) | (g<<8) | b;
	case 4:
		fz_convert_color(ctx, fz_device_cmyk(ctx), color, fz_device_rgb(ctx), rgb, NULL, fz_default_color_params);
		r = rgb[0] * 255;
		g = rgb[1] * 255;
		b = rgb[2] * 255;
		return 0xff000000 | (r<<16) | (g<<8) | b;
	}
}