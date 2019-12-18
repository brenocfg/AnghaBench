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

__attribute__((used)) static void bgr_to_gray(fz_context *ctx, fz_color_converter *cc, const float *bgr, float *gray)
{
	gray[0] = bgr[0] * 0.11f + bgr[1] * 0.59f + bgr[2] * 0.3f;
}