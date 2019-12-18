#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float a; float c; float e; float b; float d; float f; } ;
struct TYPE_5__ {int /*<<< orphan*/  rast; TYPE_1__ ctm; } ;
typedef  TYPE_2__ sctx ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_insert_rasterizer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float,float,float,float,int) ; 

__attribute__((used)) static void
fz_add_line(fz_context *ctx, sctx *s, float x0, float y0, float x1, float y1, int rev)
{
	float tx0 = s->ctm.a * x0 + s->ctm.c * y0 + s->ctm.e;
	float ty0 = s->ctm.b * x0 + s->ctm.d * y0 + s->ctm.f;
	float tx1 = s->ctm.a * x1 + s->ctm.c * y1 + s->ctm.e;
	float ty1 = s->ctm.b * x1 + s->ctm.d * y1 + s->ctm.f;

	fz_insert_rasterizer(ctx, s->rast, tx0, ty0, tx1, ty1, rev);
}