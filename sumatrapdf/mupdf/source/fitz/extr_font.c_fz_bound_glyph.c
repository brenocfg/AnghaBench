#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {float x1; float y1; scalar_t__ y0; scalar_t__ x0; } ;
typedef  TYPE_1__ fz_rect ;
typedef  int /*<<< orphan*/  fz_matrix ;
struct TYPE_12__ {int glyph_count; TYPE_1__ bbox; TYPE_1__* bbox_table; scalar_t__ t3lists; scalar_t__ ft_face; } ;
typedef  TYPE_2__ fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_bound_ft_glyph (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  fz_bound_t3_glyph (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 scalar_t__ fz_is_empty_rect (TYPE_1__) ; 
 scalar_t__ fz_is_infinite_rect (TYPE_1__) ; 
 TYPE_1__ fz_transform_rect (TYPE_1__,int /*<<< orphan*/ ) ; 

fz_rect
fz_bound_glyph(fz_context *ctx, fz_font *font, int gid, fz_matrix trm)
{
	fz_rect rect;
	if (font->bbox_table && gid < font->glyph_count)
	{
		/* If the bbox is infinite or empty, distrust it */
		if (fz_is_infinite_rect(font->bbox_table[gid]) || fz_is_empty_rect(font->bbox_table[gid]))
		{
			/* Get the real size from the glyph */
			if (font->ft_face)
				fz_bound_ft_glyph(ctx, font, gid);
			else if (font->t3lists)
				fz_bound_t3_glyph(ctx, font, gid);
			else
				/* If we can't get a real size, fall back to the font
				 * bbox. */
				font->bbox_table[gid] = font->bbox;
			/* If the real size came back as empty, then store it as
			 * a very small rectangle to avoid us calling this same
			 * check every time. */
			if (fz_is_empty_rect(font->bbox_table[gid]))
			{
				font->bbox_table[gid].x0 = 0;
				font->bbox_table[gid].y0 = 0;
				font->bbox_table[gid].x1 = 0.0000001f;
				font->bbox_table[gid].y1 = 0.0000001f;
			}
		}
		rect = font->bbox_table[gid];
	}
	else
	{
		/* fall back to font bbox */
		rect = font->bbox;
	}
	return fz_transform_rect(rect, trm);
}