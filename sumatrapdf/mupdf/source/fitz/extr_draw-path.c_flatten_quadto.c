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
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {float x; float y; } ;
struct TYPE_4__ {TYPE_1__ c; int /*<<< orphan*/  flatness; int /*<<< orphan*/  ctm; int /*<<< orphan*/  rast; } ;
typedef  TYPE_2__ flatten_arg ;

/* Variables and functions */
 int /*<<< orphan*/  quad (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,float,float,float,float,float,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
flatten_quadto(fz_context *ctx, void *arg_, float x1, float y1, float x2, float y2)
{
	flatten_arg *arg = (flatten_arg *)arg_;

	quad(ctx, arg->rast, arg->ctm, arg->flatness, arg->c.x, arg->c.y, x1, y1, x2, y2, 0);
	arg->c.x = x2;
	arg->c.y = y2;
}