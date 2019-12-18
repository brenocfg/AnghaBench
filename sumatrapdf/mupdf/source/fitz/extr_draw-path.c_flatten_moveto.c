#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {float x; float y; } ;
struct TYPE_4__ {float x; float y; } ;
struct TYPE_6__ {int /*<<< orphan*/  rast; TYPE_2__ b; TYPE_1__ c; int /*<<< orphan*/  ctm; } ;
typedef  TYPE_3__ flatten_arg ;

/* Variables and functions */
 int /*<<< orphan*/  fz_gap_rasterizer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,float,float,float) ; 

__attribute__((used)) static void
flatten_moveto(fz_context *ctx, void *arg_, float x, float y)
{
	flatten_arg *arg = (flatten_arg *)arg_;

	/* implicit closepath before moveto */
	if (arg->c.x != arg->b.x || arg->c.y != arg->b.y)
		line(ctx, arg->rast, arg->ctm, arg->c.x, arg->c.y, arg->b.x, arg->b.y);
	arg->c.x = arg->b.x = x;
	arg->c.y = arg->b.y = y;

	fz_gap_rasterizer(ctx, arg->rast);
}