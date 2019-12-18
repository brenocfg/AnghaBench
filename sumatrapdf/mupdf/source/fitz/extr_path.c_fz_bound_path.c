#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_stroke_state ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_path ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {int first; int /*<<< orphan*/  rect; scalar_t__ trailing_move; int /*<<< orphan*/  ctm; } ;
typedef  TYPE_1__ bound_path_arg ;

/* Variables and functions */
 int /*<<< orphan*/  bound_path_walker ; 
 int /*<<< orphan*/  fz_adjust_rect_for_stroke (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_empty_rect ; 
 int /*<<< orphan*/  fz_walk_path (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_1__*) ; 

fz_rect
fz_bound_path(fz_context *ctx, const fz_path *path, const fz_stroke_state *stroke, fz_matrix ctm)
{
	bound_path_arg arg;

	arg.ctm = ctm;
	arg.rect = fz_empty_rect;
	arg.trailing_move = 0;
	arg.first = 1;

	fz_walk_path(ctx, path, &bound_path_walker, &arg);

	if (!arg.first && stroke)
	{
		arg.rect = fz_adjust_rect_for_stroke(ctx, arg.rect, stroke, ctm);
	}

	return arg.rect;
}