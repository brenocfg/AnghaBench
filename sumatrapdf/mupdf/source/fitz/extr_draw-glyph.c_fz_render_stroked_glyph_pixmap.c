#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dash_len; } ;
typedef  TYPE_1__ fz_stroke_state ;
typedef  int /*<<< orphan*/  fz_pixmap ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_irect ;
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ fz_font_ft_face (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_render_ft_stroked_glyph_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/ * fz_render_glyph_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  fz_subpixel_adjust (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,unsigned char*) ; 

fz_pixmap *
fz_render_stroked_glyph_pixmap(fz_context *ctx, fz_font *font, int gid, fz_matrix *trm, fz_matrix ctm, const fz_stroke_state *stroke, const fz_irect *scissor, int aa)
{
	if (fz_font_ft_face(ctx, font))
	{
		fz_matrix subpix_trm;
		unsigned char qe, qf;

		if (stroke->dash_len > 0)
			return NULL;
		(void)fz_subpixel_adjust(ctx, trm, &subpix_trm, &qe, &qf);
		return fz_render_ft_stroked_glyph_pixmap(ctx, font, gid, subpix_trm, ctm, stroke, aa);
	}
	return fz_render_glyph_pixmap(ctx, font, gid, trm, scissor, aa);
}