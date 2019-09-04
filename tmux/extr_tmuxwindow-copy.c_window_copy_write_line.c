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
typedef  scalar_t__ u_int ;
struct window_pane {TYPE_1__* window; } ;
struct window_mode_entry {struct window_copy_mode_data* data; struct window_pane* wp; } ;
struct screen {scalar_t__ rupper; scalar_t__ rlower; } ;
struct window_copy_mode_data {scalar_t__ oy; int searchthis; scalar_t__ cy; int cx; int /*<<< orphan*/ * searchmark; int /*<<< orphan*/  backing; int /*<<< orphan*/  searchcount; struct screen screen; } ;
struct screen_write_ctx {int dummy; } ;
struct options {int dummy; } ;
struct grid_cell {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {struct options* options; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRID_FLAG_NOPALETTE ; 
 int /*<<< orphan*/  grid_default_cell ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ screen_hsize (int /*<<< orphan*/ ) ; 
 int screen_size_x (struct screen*) ; 
 int /*<<< orphan*/  screen_write_copy (struct screen_write_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,size_t,int,int /*<<< orphan*/ *,struct grid_cell*) ; 
 int /*<<< orphan*/  screen_write_cursormove (struct screen_write_ctx*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_putc (struct screen_write_ctx*,struct grid_cell*,char) ; 
 int /*<<< orphan*/  screen_write_puts (struct screen_write_ctx*,struct grid_cell*,char*,char*) ; 
 int /*<<< orphan*/  style_apply (struct grid_cell*,struct options*,char*) ; 
 size_t xsnprintf (char*,int,char*,int,scalar_t__,...) ; 

__attribute__((used)) static void
window_copy_write_line(struct window_mode_entry *wme,
    struct screen_write_ctx *ctx, u_int py)
{
	struct window_pane		*wp = wme->wp;
	struct window_copy_mode_data	*data = wme->data;
	struct screen			*s = &data->screen;
	struct options			*oo = wp->window->options;
	struct grid_cell		 gc;
	char				 hdr[512];
	size_t				 size = 0;

	style_apply(&gc, oo, "mode-style");
	gc.flags |= GRID_FLAG_NOPALETTE;

	if (py == 0 && s->rupper < s->rlower) {
		if (data->searchmark == NULL) {
			size = xsnprintf(hdr, sizeof hdr,
			    "[%u/%u]", data->oy, screen_hsize(data->backing));
		} else {
			if (data->searchthis == -1) {
				size = xsnprintf(hdr, sizeof hdr,
				    "(%u results) [%d/%u]", data->searchcount,
				    data->oy, screen_hsize(data->backing));
			} else {
				size = xsnprintf(hdr, sizeof hdr,
				    "(%u/%u results) [%d/%u]", data->searchthis,
				    data->searchcount, data->oy,
				    screen_hsize(data->backing));
			}
		}
		if (size > screen_size_x(s))
			size = screen_size_x(s);
		screen_write_cursormove(ctx, screen_size_x(s) - size, 0, 0);
		screen_write_puts(ctx, &gc, "%s", hdr);
	} else
		size = 0;

	if (size < screen_size_x(s)) {
		screen_write_cursormove(ctx, 0, py, 0);
		screen_write_copy(ctx, data->backing, 0,
		    (screen_hsize(data->backing) - data->oy) + py,
		    screen_size_x(s) - size, 1, data->searchmark, &gc);
	}

	if (py == data->cy && data->cx == screen_size_x(s)) {
		memcpy(&gc, &grid_default_cell, sizeof gc);
		screen_write_cursormove(ctx, screen_size_x(s) - 1, py, 0);
		screen_write_putc(ctx, &gc, '$');
	}
}