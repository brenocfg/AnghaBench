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
struct TYPE_4__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_5__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_6__ {TYPE_1__ b; TYPE_2__ c; int /*<<< orphan*/  ctm; int /*<<< orphan*/  rast; } ;
typedef  TYPE_3__ flatten_arg ;

/* Variables and functions */
 int /*<<< orphan*/  line (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
flatten_close(fz_context *ctx, void *arg_)
{
	flatten_arg *arg = (flatten_arg *)arg_;

	line(ctx, arg->rast, arg->ctm, arg->c.x, arg->c.y, arg->b.x, arg->b.y);
	arg->c.x = arg->b.x;
	arg->c.y = arg->b.y;
}