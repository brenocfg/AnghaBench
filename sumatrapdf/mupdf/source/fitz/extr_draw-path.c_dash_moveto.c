#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float x; float y; } ;
struct TYPE_5__ {float x; float y; } ;
struct TYPE_7__ {TYPE_2__ cur; TYPE_1__ dash_beg; } ;
typedef  TYPE_3__ sctx ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_dash_moveto (int /*<<< orphan*/ *,TYPE_3__*,float,float) ; 

__attribute__((used)) static void
dash_moveto(fz_context *ctx, void *s_, float x, float y)
{
	sctx *s = (sctx *)s_;

	fz_dash_moveto(ctx, s, x, y);
	s->dash_beg.x = s->cur.x = x;
	s->dash_beg.y = s->cur.y = y;
}