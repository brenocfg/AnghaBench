#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float x0; float y0; float x1; float y1; } ;
struct TYPE_6__ {int invalid_bbox; } ;
struct TYPE_7__ {TYPE_3__ bbox; TYPE_1__ flags; scalar_t__ t3procs; } ;
typedef  TYPE_2__ fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_3__ fz_empty_rect ; 
 TYPE_3__ fz_unit_rect ; 

void
fz_set_font_bbox(fz_context *ctx, fz_font *font, float xmin, float ymin, float xmax, float ymax)
{
	if (xmin >= xmax || ymin >= ymax)
	{
		/* Invalid bbox supplied. */
		if (font->t3procs)
		{
			/* For type3 fonts we use the union of all the glyphs' bboxes. */
			font->bbox = fz_empty_rect;
		}
		else
		{
			/* For other fonts it would be prohibitively slow to measure the true one, so make one up. */
			font->bbox = fz_unit_rect;
		}
		font->flags.invalid_bbox = 1;
	}
	else
	{
		font->bbox.x0 = xmin;
		font->bbox.y0 = ymin;
		font->bbox.x1 = xmax;
		font->bbox.y1 = ymax;
	}
}