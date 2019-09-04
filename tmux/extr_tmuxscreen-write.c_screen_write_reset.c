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
struct screen_write_ctx {struct screen* s; } ;
struct screen {int mode; } ;

/* Variables and functions */
 int MODE_CURSOR ; 
 int MODE_WRAP ; 
 int /*<<< orphan*/  screen_reset_tabs (struct screen*) ; 
 scalar_t__ screen_size_y (struct screen*) ; 
 int /*<<< orphan*/  screen_write_clearscreen (struct screen_write_ctx*,int) ; 
 int /*<<< orphan*/  screen_write_scrollregion (struct screen_write_ctx*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  screen_write_set_cursor (struct screen_write_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
screen_write_reset(struct screen_write_ctx *ctx)
{
	struct screen	*s = ctx->s;

	screen_reset_tabs(s);
	screen_write_scrollregion(ctx, 0, screen_size_y(s) - 1);

	s->mode = MODE_CURSOR | MODE_WRAP;

	screen_write_clearscreen(ctx, 8);
	screen_write_set_cursor(ctx, 0, 0);
}