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
struct TYPE_4__ {float x; float y; } ;
struct TYPE_5__ {TYPE_1__ cur; } ;
typedef  TYPE_2__ sctx ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_stroke_bezier (int /*<<< orphan*/ *,TYPE_2__*,float,float,float,float,float,float,float,float,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
stroke_curveto(fz_context *ctx, void *s_, float x1, float y1, float x2, float y2, float x3, float y3)
{
	sctx *s = (sctx *)s_;

	fz_stroke_bezier(ctx, s, s->cur.x, s->cur.y, x1, y1, x2, y2, x3, y3, 0);
	s->cur.x = x3;
	s->cur.y = y3;
}