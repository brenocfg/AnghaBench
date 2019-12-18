#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct screen_write_ctx {struct screen* s; } ;
struct screen {size_t cx; size_t cy; } ;
struct menu {size_t width; size_t count; char const* title; TYPE_1__* items; } ;
struct grid_cell {int /*<<< orphan*/  attr; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRID_ATTR_DIM ; 
 int /*<<< orphan*/  GRID_ATTR_REVERSE ; 
 int /*<<< orphan*/  format_draw (struct screen_write_ctx*,struct grid_cell*,size_t,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grid_default_cell ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  screen_write_box (struct screen_write_ctx*,size_t,size_t) ; 
 int /*<<< orphan*/  screen_write_cursormove (struct screen_write_ctx*,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_hline (struct screen_write_ctx*,size_t,int,int) ; 
 int /*<<< orphan*/  screen_write_putc (struct screen_write_ctx*,struct grid_cell*,char) ; 
 int /*<<< orphan*/  screen_write_set_cursor (struct screen_write_ctx*,size_t,size_t) ; 

void
screen_write_menu(struct screen_write_ctx *ctx, struct menu *menu, int choice)
{
	struct screen		*s = ctx->s;
	struct grid_cell	 gc;
	u_int			 cx, cy, i, j;
	const char		*name;

	cx = s->cx;
	cy = s->cy;

	memcpy(&gc, &grid_default_cell, sizeof gc);

	screen_write_box(ctx, menu->width + 4, menu->count + 2);
	screen_write_cursormove(ctx, cx + 2, cy, 0);
	format_draw(ctx, &gc, menu->width, menu->title, NULL);

	for (i = 0; i < menu->count; i++) {
		name = menu->items[i].name;
		if (name == NULL) {
			screen_write_cursormove(ctx, cx, cy + 1 + i, 0);
			screen_write_hline(ctx, menu->width + 4, 1, 1);
		} else {
			if (choice >= 0 && i == (u_int)choice && *name != '-')
				gc.attr |= GRID_ATTR_REVERSE;
			screen_write_cursormove(ctx, cx + 2, cy + 1 + i, 0);
			for (j = 0; j < menu->width; j++)
				screen_write_putc(ctx, &gc, ' ');
			screen_write_cursormove(ctx, cx + 2, cy + 1 + i, 0);
			if (*name == '-') {
				name++;
				gc.attr |= GRID_ATTR_DIM;
				format_draw(ctx, &gc, menu->width, name, NULL);
				gc.attr &= ~GRID_ATTR_DIM;
			} else
				format_draw(ctx, &gc, menu->width, name, NULL);
			if (choice >= 0 && i == (u_int)choice)
				gc.attr &= ~GRID_ATTR_REVERSE;
		}
	}

	screen_write_set_cursor(ctx, cx, cy);
}