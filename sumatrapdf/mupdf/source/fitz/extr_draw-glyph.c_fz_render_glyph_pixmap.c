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
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_irect ;
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 float MAX_GLYPH_SIZE ; 
 int /*<<< orphan*/  fz_font_ft_face (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fz_font_t3_procs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_infinite_irect ; 
 int /*<<< orphan*/ * fz_render_ft_glyph_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * fz_render_t3_glyph_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 float fz_subpixel_adjust (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 

fz_pixmap *
fz_render_glyph_pixmap(fz_context *ctx, fz_font *font, int gid, fz_matrix *ctm, const fz_irect *scissor, int aa)
{
	fz_pixmap *val = NULL;
	unsigned char qe, qf;
	fz_matrix subpix_ctm;
	float size = fz_subpixel_adjust(ctx, ctm, &subpix_ctm, &qe, &qf);
	int is_ft_font = !!fz_font_ft_face(ctx, font);

	if (size <= MAX_GLYPH_SIZE)
	{
		scissor = &fz_infinite_irect;
	}
	else
	{
		if (is_ft_font)
			return NULL;
	}

	if (is_ft_font)
	{
		val = fz_render_ft_glyph_pixmap(ctx, font, gid, subpix_ctm, aa);
	}
	else if (fz_font_t3_procs(ctx, font))
	{
		val = fz_render_t3_glyph_pixmap(ctx, font, gid, subpix_ctm, NULL, scissor, aa);
	}
	else
	{
		fz_warn(ctx, "assert: uninitialized font structure");
		val = NULL;
	}

	return val;
}