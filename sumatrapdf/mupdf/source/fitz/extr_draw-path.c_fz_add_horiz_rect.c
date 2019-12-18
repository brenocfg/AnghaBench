#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float b; float c; float a; float e; float d; float f; } ;
struct TYPE_6__ {int /*<<< orphan*/  rast; TYPE_1__ ctm; } ;
typedef  TYPE_2__ sctx ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_add_line (int /*<<< orphan*/ *,TYPE_2__*,float,float,float,float,int) ; 
 scalar_t__ fz_antidropout_rasterizer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_insert_rasterizer_rect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float,float,float,float) ; 

__attribute__((used)) static void
fz_add_horiz_rect(fz_context *ctx, sctx *s, float x0, float y0, float x1, float y1)
{
	if (fz_antidropout_rasterizer(ctx, s->rast)) {
		if (s->ctm.b == 0 && s->ctm.c == 0)
		{
			float tx0 = s->ctm.a * x0 + s->ctm.e;
			float ty0 = s->ctm.d * y0 + s->ctm.f;
			float tx1 = s->ctm.a * x1 + s->ctm.e;
			float ty1 = s->ctm.d * y1 + s->ctm.f;
			fz_insert_rasterizer_rect(ctx, s->rast, tx1, ty1, tx0, ty0);
			return;
		}
		else if (s->ctm.a == 0 && s->ctm.d == 0)
		{
			float tx0 = s->ctm.c * y0 + s->ctm.e;
			float ty0 = s->ctm.b * x0 + s->ctm.f;
			float tx1 = s->ctm.c * y1 + s->ctm.e;
			float ty1 = s->ctm.b * x1 + s->ctm.f;
			fz_insert_rasterizer_rect(ctx, s->rast, tx1, ty0, tx0, ty1);
			return;
		}
	}

	fz_add_line(ctx, s, x0, y0, x1, y0, 0);
	fz_add_line(ctx, s, x1, y1, x0, y1, 1);
}