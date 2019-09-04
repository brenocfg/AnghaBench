#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u_int ;
struct screen_write_ctx {struct screen* s; } ;
struct screen {scalar_t__ cx; scalar_t__ cy; } ;

/* Variables and functions */
 int /*<<< orphan*/  screen_write_set_cursor (struct screen_write_ctx*,scalar_t__,scalar_t__) ; 

void
screen_write_cursorleft(struct screen_write_ctx *ctx, u_int nx)
{
	struct screen	*s = ctx->s;
	u_int		 cx = s->cx, cy = s->cy;

	if (nx == 0)
		nx = 1;

	if (nx > cx)
		nx = cx;
	if (nx == 0)
		return;

	cx -= nx;

	screen_write_set_cursor(ctx, cx, cy);
}