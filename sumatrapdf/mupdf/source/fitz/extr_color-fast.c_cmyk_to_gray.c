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
 int fz_min (float,int) ; 

__attribute__((used)) static void cmyk_to_gray(fz_context *ctx, fz_color_converter *cc, const float *cmyk, float *gray)
{
	float c = cmyk[0] * 0.3f;
	float m = cmyk[1] * 0.59f;
	float y = cmyk[2] * 0.11f;
	gray[0] = 1 - fz_min(c + m + y + cmyk[3], 1);
}