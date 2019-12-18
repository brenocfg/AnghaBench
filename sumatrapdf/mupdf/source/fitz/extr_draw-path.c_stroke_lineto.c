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
 int /*<<< orphan*/  fz_stroke_lineto (int /*<<< orphan*/ *,TYPE_2__*,float,float,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
stroke_lineto(fz_context *ctx, void *s_, float x, float y)
{
	sctx *s = (sctx *)s_;

	fz_stroke_lineto(ctx, s, x, y, 0);
	s->cur.x = x;
	s->cur.y = y;
}