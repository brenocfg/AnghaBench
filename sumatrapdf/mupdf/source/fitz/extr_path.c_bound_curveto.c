#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ fz_point ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {int /*<<< orphan*/  y1; int /*<<< orphan*/  y0; int /*<<< orphan*/  x1; int /*<<< orphan*/  x0; } ;
struct TYPE_7__ {TYPE_1__ move; TYPE_4__ rect; scalar_t__ trailing_move; int /*<<< orphan*/  ctm; scalar_t__ first; } ;
typedef  TYPE_2__ bound_path_arg ;

/* Variables and functions */
 int /*<<< orphan*/  bound_expand (TYPE_4__*,TYPE_1__) ; 
 TYPE_1__ fz_transform_point_xy (float,float,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bound_curveto(fz_context *ctx, void *arg_, float x1, float y1, float x2, float y2, float x3, float y3)
{
	bound_path_arg *arg = (bound_path_arg *)arg_;
	fz_point p = fz_transform_point_xy(x1, y1, arg->ctm);
	if (arg->first)
	{
		arg->rect.x0 = arg->rect.x1 = p.x;
		arg->rect.y0 = arg->rect.y1 = p.y;
		arg->first = 0;
	}
	else
		bound_expand(&arg->rect, p);
	bound_expand(&arg->rect, fz_transform_point_xy(x2, y2, arg->ctm));
	bound_expand(&arg->rect, fz_transform_point_xy(x3, y3, arg->ctm));
	if (arg->trailing_move)
	{
		arg->trailing_move = 0;
		bound_expand(&arg->rect, arg->move);
	}
}