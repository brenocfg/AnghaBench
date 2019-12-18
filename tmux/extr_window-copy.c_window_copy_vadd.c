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
typedef  int /*<<< orphan*/  va_list ;
typedef  int u_int ;
struct screen {int cy; } ;
struct window_pane {struct screen base; int /*<<< orphan*/  modes; } ;
struct window_mode_entry {struct window_copy_mode_data* data; } ;
struct window_copy_mode_data {int backing_written; struct screen* backing; struct screen screen; int /*<<< orphan*/  oy; } ;
struct screen_write_ctx {int dummy; } ;
struct grid_cell {int dummy; } ;

/* Variables and functions */
 struct window_mode_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grid_default_cell ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,int /*<<< orphan*/ *,int) ; 
 int screen_hsize (struct screen*) ; 
 int /*<<< orphan*/  screen_write_carriagereturn (struct screen_write_ctx*) ; 
 int /*<<< orphan*/  screen_write_linefeed (struct screen_write_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  screen_write_start (struct screen_write_ctx*,struct window_pane*,struct screen*) ; 
 int /*<<< orphan*/  screen_write_stop (struct screen_write_ctx*) ; 
 int /*<<< orphan*/  screen_write_vnputs (struct screen_write_ctx*,int /*<<< orphan*/ ,struct grid_cell*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_copy_redraw_lines (struct window_mode_entry*,int,int) ; 

void
window_copy_vadd(struct window_pane *wp, const char *fmt, va_list ap)
{
	struct window_mode_entry	*wme = TAILQ_FIRST(&wp->modes);
	struct window_copy_mode_data	*data = wme->data;
	struct screen			*backing = data->backing;
	struct screen_write_ctx	 	 back_ctx, ctx;
	struct grid_cell		 gc;
	u_int				 old_hsize, old_cy;

	if (backing == &wp->base)
		return;

	memcpy(&gc, &grid_default_cell, sizeof gc);

	old_hsize = screen_hsize(data->backing);
	screen_write_start(&back_ctx, NULL, backing);
	if (data->backing_written) {
		/*
		 * On the second or later line, do a CRLF before writing
		 * (so it's on a new line).
		 */
		screen_write_carriagereturn(&back_ctx);
		screen_write_linefeed(&back_ctx, 0, 8);
	} else
		data->backing_written = 1;
	old_cy = backing->cy;
	screen_write_vnputs(&back_ctx, 0, &gc, fmt, ap);
	screen_write_stop(&back_ctx);

	data->oy += screen_hsize(data->backing) - old_hsize;

	screen_write_start(&ctx, wp, &data->screen);

	/*
	 * If the history has changed, draw the top line.
	 * (If there's any history at all, it has changed.)
	 */
	if (screen_hsize(data->backing))
		window_copy_redraw_lines(wme, 0, 1);

	/* Write the new lines. */
	window_copy_redraw_lines(wme, old_cy, backing->cy - old_cy + 1);

	screen_write_stop(&ctx);
}