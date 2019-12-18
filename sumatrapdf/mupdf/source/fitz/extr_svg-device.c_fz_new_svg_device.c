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
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_new_svg_device_with_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,float,int,int,int /*<<< orphan*/ *) ; 

fz_device *fz_new_svg_device(fz_context *ctx, fz_output *out, float page_width, float page_height, int text_format, int reuse_images)
{
	return fz_new_svg_device_with_id(ctx, out, page_width, page_height, text_format, reuse_images, NULL);
}