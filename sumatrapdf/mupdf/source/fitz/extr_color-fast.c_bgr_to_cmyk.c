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
typedef  int /*<<< orphan*/  fz_color_converter ;

/* Variables and functions */
 float fz_min (float,float) ; 

__attribute__((used)) static void bgr_to_cmyk(fz_context *ctx, fz_color_converter *cc, const float *bgr, float *cmyk)
{
	float c, m, y, k;
	c = 1 - bgr[2];
	m = 1 - bgr[1];
	y = 1 - bgr[0];
	k = fz_min(c, fz_min(m, y));
	cmyk[0] = c - k;
	cmyk[1] = m - k;
	cmyk[2] = y - k;
	cmyk[3] = k;
}