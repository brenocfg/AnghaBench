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
struct screen {int dummy; } ;
struct window_pane {struct screen base; } ;
struct window_mode_entry {struct window_copy_mode_data* data; struct window_pane* wp; } ;
struct window_copy_mode_data {scalar_t__ oy; scalar_t__ searcho; int /*<<< orphan*/  cy; int /*<<< orphan*/  searchy; scalar_t__ cx; scalar_t__ searchx; int /*<<< orphan*/ * searchmark; struct screen* backing; struct screen screen; } ;
struct screen_write_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ screen_hsize (struct screen*) ; 
 int /*<<< orphan*/  screen_resize (struct screen*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ screen_size_y (struct screen*) ; 
 int /*<<< orphan*/  screen_write_start (struct screen_write_ctx*,int /*<<< orphan*/ *,struct screen*) ; 
 int /*<<< orphan*/  screen_write_stop (struct screen_write_ctx*) ; 
 int /*<<< orphan*/  window_copy_clear_marks (struct window_mode_entry*) ; 
 int /*<<< orphan*/  window_copy_clear_selection (struct window_mode_entry*) ; 
 int /*<<< orphan*/  window_copy_redraw_screen (struct window_mode_entry*) ; 
 int /*<<< orphan*/  window_copy_search_marks (struct window_mode_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  window_copy_write_lines (struct window_mode_entry*,struct screen_write_ctx*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
window_copy_resize(struct window_mode_entry *wme, u_int sx, u_int sy)
{
	struct window_pane		*wp = wme->wp;
	struct window_copy_mode_data	*data = wme->data;
	struct screen			*s = &data->screen;
	struct screen_write_ctx	 	 ctx;
	int				 search;

	screen_resize(s, sx, sy, 1);
	if (data->backing != &wp->base)
		screen_resize(data->backing, sx, sy, 1);

	if (data->cy > sy - 1)
		data->cy = sy - 1;
	if (data->cx > sx)
		data->cx = sx;
	if (data->oy > screen_hsize(data->backing))
		data->oy = screen_hsize(data->backing);

	search = (data->searchmark != NULL);
	window_copy_clear_selection(wme);
	window_copy_clear_marks(wme);

	screen_write_start(&ctx, NULL, s);
	window_copy_write_lines(wme, &ctx, 0, screen_size_y(s) - 1);
	screen_write_stop(&ctx);

	if (search)
		window_copy_search_marks(wme, NULL);
	data->searchx = data->cx;
	data->searchy = data->cy;
	data->searcho = data->oy;

	window_copy_redraw_screen(wme);
}