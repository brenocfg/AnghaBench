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
 int fz_min (float const,int) ; 

__attribute__((used)) static void cmyk_to_bgr(fz_context *ctx, fz_color_converter *cc, const float *cmyk, float *bgr)
{
	bgr[0] = 1 - fz_min(cmyk[2] + cmyk[3], 1);
	bgr[1] = 1 - fz_min(cmyk[1] + cmyk[3], 1);
	bgr[2] = 1 - fz_min(cmyk[0] + cmyk[3], 1);
}