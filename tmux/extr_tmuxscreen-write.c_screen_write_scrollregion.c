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
typedef  int u_int ;
struct screen_write_ctx {struct screen* s; } ;
struct screen {int rupper; int rlower; } ;

/* Variables and functions */
 int screen_size_y (struct screen*) ; 
 int /*<<< orphan*/  screen_write_collect_flush (struct screen_write_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_set_cursor (struct screen_write_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
screen_write_scrollregion(struct screen_write_ctx *ctx, u_int rupper,
    u_int rlower)
{
	struct screen	*s = ctx->s;

	if (rupper > screen_size_y(s) - 1)
		rupper = screen_size_y(s) - 1;
	if (rlower > screen_size_y(s) - 1)
		rlower = screen_size_y(s) - 1;
	if (rupper >= rlower)	/* cannot be one line */
		return;

	screen_write_collect_flush(ctx, 0);

	/* Cursor moves to top-left. */
	screen_write_set_cursor(ctx, 0, 0);

	s->rupper = rupper;
	s->rlower = rlower;
}