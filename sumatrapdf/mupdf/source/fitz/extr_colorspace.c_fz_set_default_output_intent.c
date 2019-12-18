#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  cmyk; int /*<<< orphan*/ * oi; int /*<<< orphan*/  rgb; int /*<<< orphan*/  gray; } ;
typedef  TYPE_1__ fz_default_colorspaces ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_13__ {int type; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ fz_colorspace ;

/* Variables and functions */
#define  FZ_COLORSPACE_CMYK 130 
#define  FZ_COLORSPACE_GRAY 129 
#define  FZ_COLORSPACE_RGB 128 
 int /*<<< orphan*/  fz_device_cmyk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_device_gray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_device_rgb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* fz_keep_colorspace (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  fz_set_default_cmyk (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  fz_set_default_gray (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  fz_set_default_rgb (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void fz_set_default_output_intent(fz_context *ctx, fz_default_colorspaces *default_cs, fz_colorspace *cs)
{
	fz_drop_colorspace(ctx, default_cs->oi);
	default_cs->oi = NULL;

	/* FIXME: Why do we set DefaultXXX along with the output intent?! */
	switch (cs->type)
	{
	default:
		fz_warn(ctx, "Ignoring incompatible output intent: %s.", cs->name);
		break;
	case FZ_COLORSPACE_GRAY:
		default_cs->oi = fz_keep_colorspace(ctx, cs);
		if (default_cs->gray == fz_device_gray(ctx))
			fz_set_default_gray(ctx, default_cs, cs);
		break;
	case FZ_COLORSPACE_RGB:
		default_cs->oi = fz_keep_colorspace(ctx, cs);
		if (default_cs->rgb == fz_device_rgb(ctx))
			fz_set_default_rgb(ctx, default_cs, cs);
		break;
	case FZ_COLORSPACE_CMYK:
		default_cs->oi = fz_keep_colorspace(ctx, cs);
		if (default_cs->cmyk == fz_device_cmyk(ctx))
			fz_set_default_cmyk(ctx, default_cs, cs);
		break;
	}
}