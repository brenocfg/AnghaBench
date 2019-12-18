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
typedef  int /*<<< orphan*/  fz_default_colorspaces ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
#define  FZ_COLORSPACE_CMYK 130 
#define  FZ_COLORSPACE_GRAY 129 
#define  FZ_COLORSPACE_RGB 128 
 int fz_colorspace_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_default_cmyk (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_default_gray (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_default_rgb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_device_cmyk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_device_gray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_device_rgb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static fz_colorspace *fz_default_colorspace(fz_context *ctx, fz_default_colorspaces *default_cs, fz_colorspace *cs)
{
	if (cs == NULL)
		return NULL;
	if (default_cs == NULL)
		return cs;

	switch (fz_colorspace_type(ctx, cs))
	{
	case FZ_COLORSPACE_GRAY:
		if (cs == fz_device_gray(ctx))
			return fz_default_gray(ctx, default_cs);
		break;
	case FZ_COLORSPACE_RGB:
		if (cs == fz_device_rgb(ctx))
			return fz_default_rgb(ctx, default_cs);
		break;
	case FZ_COLORSPACE_CMYK:
		if (cs == fz_device_cmyk(ctx))
			return fz_default_cmyk(ctx, default_cs);
		break;
	default:
		break;
	}
	return cs;
}