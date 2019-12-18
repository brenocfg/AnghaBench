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
typedef  int /*<<< orphan*/  fz_pixmap ;

/* Variables and functions */
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  currentaa ; 
 scalar_t__ currentinvert ; 
 scalar_t__ currenttint ; 
 int /*<<< orphan*/  draw_page_ctm ; 
 int /*<<< orphan*/  fz_device_rgb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_gamma_pixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_invert_pixmap_luminance (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_new_pixmap_from_page_with_separations (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_set_aa_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_tint_pixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fzpage ; 
 int /*<<< orphan*/  page_tex ; 
 int /*<<< orphan*/  seps ; 
 int /*<<< orphan*/  tint_black ; 
 int /*<<< orphan*/  tint_white ; 
 int /*<<< orphan*/  transform_page () ; 
 int /*<<< orphan*/  ui_texture_from_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void render_page(void)
{
	fz_pixmap *pix;

	transform_page();

	fz_set_aa_level(ctx, currentaa);

	pix = fz_new_pixmap_from_page_with_separations(ctx, fzpage, draw_page_ctm, fz_device_rgb(ctx), seps, 0);
	if (currentinvert)
	{
		fz_invert_pixmap_luminance(ctx, pix);
		fz_gamma_pixmap(ctx, pix, 1 / 1.4f);
	}
	if (currenttint)
	{
		fz_tint_pixmap(ctx, pix, tint_black, tint_white);
	}

	ui_texture_from_pixmap(&page_tex, pix);
	fz_drop_pixmap(ctx, pix);
}