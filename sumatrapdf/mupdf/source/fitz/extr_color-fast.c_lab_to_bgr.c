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
 int /*<<< orphan*/  lab_to_rgb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float const*,float*) ; 
 int /*<<< orphan*/  rgb_to_bgr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float*,float*) ; 

__attribute__((used)) static void lab_to_bgr(fz_context *ctx, fz_color_converter *cc, const float *lab, float *bgr)
{
	float rgb[3];
	lab_to_rgb(ctx, cc, lab, rgb);
	rgb_to_bgr(ctx, cc, rgb, bgr);
}