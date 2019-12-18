#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float linewidth; scalar_t__ linejoin; int miterlimit; } ;
typedef  TYPE_1__ fz_stroke_state ;
struct TYPE_7__ {float x0; float y0; float x1; float y1; } ;
typedef  TYPE_2__ fz_rect ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ FZ_LINEJOIN_MITER ; 
 scalar_t__ FZ_LINEJOIN_MITER_XPS ; 
 float fz_matrix_max_expansion (int /*<<< orphan*/ ) ; 

fz_rect
fz_adjust_rect_for_stroke(fz_context *ctx, fz_rect r, const fz_stroke_state *stroke, fz_matrix ctm)
{
	float expand;

	if (!stroke)
		return r;

	expand = stroke->linewidth;
	if (expand == 0)
		expand = 1.0f;
	expand *= fz_matrix_max_expansion(ctm);
	if ((stroke->linejoin == FZ_LINEJOIN_MITER || stroke->linejoin == FZ_LINEJOIN_MITER_XPS) && stroke->miterlimit > 1)
		expand *= stroke->miterlimit;

	r.x0 -= expand;
	r.y0 -= expand;
	r.x1 += expand;
	r.y1 += expand;
	return r;
}