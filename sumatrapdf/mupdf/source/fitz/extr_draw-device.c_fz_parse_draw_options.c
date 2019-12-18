#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int x_resolution; int y_resolution; void* height; void* width; void* text; void* graphics; scalar_t__ alpha; void* colorspace; void* rotate; } ;
typedef  TYPE_1__ fz_draw_options ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 void* fz_aa_level (int /*<<< orphan*/ *) ; 
 void* fz_atoi (char const*) ; 
 void* fz_device_cmyk (int /*<<< orphan*/ *) ; 
 void* fz_device_gray (int /*<<< orphan*/ *) ; 
 void* fz_device_rgb (int /*<<< orphan*/ *) ; 
 scalar_t__ fz_has_option (int /*<<< orphan*/ *,char const*,char*,char const**) ; 
 scalar_t__ fz_option_eq (char const*,char*) ; 
 void* fz_text_aa_level (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* parse_aa_opts (char const*) ; 

fz_draw_options *
fz_parse_draw_options(fz_context *ctx, fz_draw_options *opts, const char *args)
{
	const char *val;

	memset(opts, 0, sizeof *opts);

	opts->x_resolution = 96;
	opts->y_resolution = 96;
	opts->rotate = 0;
	opts->width = 0;
	opts->height = 0;
	opts->colorspace = fz_device_rgb(ctx);
	opts->alpha = 0;
	opts->graphics = fz_aa_level(ctx);
	opts->text = fz_text_aa_level(ctx);

	if (fz_has_option(ctx, args, "rotate", &val))
		opts->rotate = fz_atoi(val);
	if (fz_has_option(ctx, args, "resolution", &val))
		opts->x_resolution = opts->y_resolution = fz_atoi(val);
	if (fz_has_option(ctx, args, "x-resolution", &val))
		opts->x_resolution = fz_atoi(val);
	if (fz_has_option(ctx, args, "y-resolution", &val))
		opts->y_resolution = fz_atoi(val);
	if (fz_has_option(ctx, args, "width", &val))
		opts->width = fz_atoi(val);
	if (fz_has_option(ctx, args, "height", &val))
		opts->height = fz_atoi(val);
	if (fz_has_option(ctx, args, "colorspace", &val))
	{
		if (fz_option_eq(val, "gray") || fz_option_eq(val, "grey") || fz_option_eq(val, "mono"))
			opts->colorspace = fz_device_gray(ctx);
		else if (fz_option_eq(val, "rgb"))
			opts->colorspace = fz_device_rgb(ctx);
		else if (fz_option_eq(val, "cmyk"))
			opts->colorspace = fz_device_cmyk(ctx);
		else
			fz_throw(ctx, FZ_ERROR_GENERIC, "unknown colorspace in options");
	}
	if (fz_has_option(ctx, args, "alpha", &val))
		opts->alpha = fz_option_eq(val, "yes");
	if (fz_has_option(ctx, args, "graphics", &val))
		opts->text = opts->graphics = parse_aa_opts(val);
	if (fz_has_option(ctx, args, "text", &val))
		opts->text = parse_aa_opts(val);

	/* Sanity check values */
	if (opts->x_resolution <= 0) opts->x_resolution = 96;
	if (opts->y_resolution <= 0) opts->y_resolution = 96;
	if (opts->width < 0) opts->width = 0;
	if (opts->height < 0) opts->height = 0;

	return opts;
}