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
struct screen {int cx; int cy; } ;
struct grid_cell {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRID_ATTR_CHARSET ; 
 int /*<<< orphan*/  grid_default_cell ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  screen_write_putc (struct screen_write_ctx*,struct grid_cell*,unsigned char) ; 
 int /*<<< orphan*/  screen_write_set_cursor (struct screen_write_ctx*,int,int) ; 

void
screen_write_hline(struct screen_write_ctx *ctx, u_int nx, int left, int right)
{
	struct screen		*s = ctx->s;
	struct grid_cell	 gc;
	u_int			 cx, cy, i;

	cx = s->cx;
	cy = s->cy;

	memcpy(&gc, &grid_default_cell, sizeof gc);
	gc.attr |= GRID_ATTR_CHARSET;

	screen_write_putc(ctx, &gc, left ? 't' : 'q');
	for (i = 1; i < nx - 1; i++)
		screen_write_putc(ctx, &gc, 'q');
	screen_write_putc(ctx, &gc, right ? 'u' : 'q');

	screen_write_set_cursor(ctx, cx, cy);
}