#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  colorspace; scalar_t__ seps; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 char* fz_colorspace_colorant (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ fz_colorspace_device_n_has_cmyk (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fz_colorspace_device_n_has_only_cmyk (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fz_colorspace_is_subtractive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fz_colorspace_n (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int
colors_supported(fz_context *ctx, fz_colorspace *cs, fz_pixmap *dest)
{
	/* Even if we support separations in the destination, if the color space has CMY or K as one of
	 * its colorants and we are in RGB or Gray we will want to do the tint transform */
	if (!fz_colorspace_is_subtractive(ctx, dest->colorspace) && fz_colorspace_device_n_has_cmyk(ctx, cs))
		return 0;

	/* If we have separations then we should support it */
	if (dest->seps)
		return 1;

	/* If our destination is CMYK and the source color space is only C, M, Y or K we support it
	 * even if we have no seps */
	if (fz_colorspace_is_subtractive(ctx, dest->colorspace))
	{
		int i, n;
		if (fz_colorspace_device_n_has_only_cmyk(ctx, cs))
			return 1;

		n = fz_colorspace_n(ctx, cs);
		for (i = 0; i < n; i++)
		{
			const char *name = fz_colorspace_colorant(ctx, cs, i);

			if (!name)
				return 0;
			if (!strcmp(name, "All"))
				continue;
			if (!strcmp(name, "Cyan"))
				continue;
			if (!strcmp(name, "Magenta"))
				continue;
			if (!strcmp(name, "Yellow"))
				continue;
			if (!strcmp(name, "Black"))
				continue;
			if (!strcmp(name, "None"))
				continue;
			return 0;
		}
		return 1;
	}

	return 0;
}