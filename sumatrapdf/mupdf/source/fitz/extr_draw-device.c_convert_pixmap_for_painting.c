#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int n; int alpha; int /*<<< orphan*/ * colorspace; scalar_t__ seps; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_overprint ;
struct TYPE_14__ {int /*<<< orphan*/  default_cs; } ;
typedef  TYPE_2__ fz_draw_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;

/* Variables and functions */
 scalar_t__ FZ_COLORSPACE_CMYK ; 
 TYPE_1__* fz_clone_pixmap_area_with_different_seps (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fz_colorspace_is_device_n (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fz_colorspace_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* fz_convert_pixmap (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_set_overprint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * set_op_from_spaces (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static fz_pixmap *
convert_pixmap_for_painting(fz_context *ctx, fz_pixmap *pixmap, fz_colorspace *model, fz_colorspace *src_cs, fz_pixmap *dest, fz_color_params color_params, fz_draw_device *dev, fz_overprint **eop)
{
	fz_pixmap *converted;

	if (fz_colorspace_is_device_n(ctx, src_cs) && dest->seps)
	{
		converted = fz_clone_pixmap_area_with_different_seps(ctx, pixmap, NULL, model, dest->seps, color_params, dev->default_cs);
		*eop = set_op_from_spaces(ctx, *eop, dest, src_cs, 0);
	}
	else
	{
		converted = fz_convert_pixmap(ctx, pixmap, model, NULL, dev->default_cs, color_params, 1);
		if (*eop)
		{
			if (fz_colorspace_type(ctx, model) != FZ_COLORSPACE_CMYK)
			{
				/* Can only overprint to CMYK based spaces */
				*eop = NULL;
			}
			else if (!fz_colorspace_is_device_n(ctx, pixmap->colorspace))
			{
				int i;
				int n = dest->n - dest->alpha;
				for (i = 4; i < n; i++)
					fz_set_overprint(*eop, i);
			}
			else
			{
				*eop = set_op_from_spaces(ctx, *eop, dest, src_cs, 0);
			}
		}
	}
	fz_drop_pixmap(ctx, pixmap);

	return converted;
}