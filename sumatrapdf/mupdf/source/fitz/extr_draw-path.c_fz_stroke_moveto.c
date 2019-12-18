#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sctx {int sn; scalar_t__ from_bezier; int /*<<< orphan*/  dot; TYPE_1__* beg; TYPE_2__* seg; } ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {float x; float y; } ;
struct TYPE_3__ {float x; float y; } ;

/* Variables and functions */
 int /*<<< orphan*/  ONLY_MOVES ; 

__attribute__((used)) static void
fz_stroke_moveto(fz_context *ctx, void *s_, float x, float y)
{
	struct sctx *s = (struct sctx *)s_;

	s->seg[0].x = s->beg[0].x = x;
	s->seg[0].y = s->beg[0].y = y;
	s->sn = 1;
	s->dot = ONLY_MOVES;
	s->from_bezier = 0;
}