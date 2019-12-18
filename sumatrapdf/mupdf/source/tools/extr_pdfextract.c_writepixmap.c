#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_6__* colorspace; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_11__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ FZ_COLORSPACE_GRAY ; 
 scalar_t__ FZ_COLORSPACE_RGB ; 
 TYPE_1__* fz_convert_pixmap (int /*<<< orphan*/ *,TYPE_1__*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_default_color_params ; 
 TYPE_6__* fz_device_rgb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_save_pixmap_as_pam (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  fz_save_pixmap_as_png (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  fz_snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void writepixmap(fz_context *ctx, fz_pixmap *pix, char *file, int dorgb)
{
	char buf[1024];
	fz_pixmap *rgb = NULL;

	if (!pix)
		return;

	if (dorgb && pix->colorspace && pix->colorspace != fz_device_rgb(ctx))
	{
		rgb = fz_convert_pixmap(ctx, pix, fz_device_rgb(ctx), NULL, NULL, fz_default_color_params /* FIXME */, 1);
		pix = rgb;
	}

	if (!pix->colorspace || pix->colorspace->type == FZ_COLORSPACE_GRAY || pix->colorspace->type == FZ_COLORSPACE_RGB)
	{
		fz_snprintf(buf, sizeof(buf), "%s.png", file);
		printf("extracting image %s\n", buf);
		fz_save_pixmap_as_png(ctx, pix, buf);
	}
	else
	{
		fz_snprintf(buf, sizeof(buf), "%s.pam", file);
		printf("extracting image %s\n", buf);
		fz_save_pixmap_as_pam(ctx, pix, buf);
	}

	fz_drop_pixmap(ctx, rgb);
}