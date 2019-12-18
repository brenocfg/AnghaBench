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
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 scalar_t__ fz_colorspace_is_cmyk (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fz_colorspace_is_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int fz_colorspace_is_device_cmyk(fz_context *ctx, fz_colorspace *cs)
{
	return fz_colorspace_is_device(ctx, cs) && fz_colorspace_is_cmyk(ctx, cs);
}