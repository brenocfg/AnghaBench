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
struct window_pane {int dummy; } ;
struct window_mode_entry {struct window_copy_mode_data* data; struct window_pane* wp; } ;
struct screen {int dummy; } ;
struct window_copy_mode_data {scalar_t__ cx; scalar_t__ cy; struct screen screen; } ;
struct screen_write_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ screen_size_x (struct screen*) ; 
 int /*<<< orphan*/  screen_write_cursormove (struct screen_write_ctx*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_start (struct screen_write_ctx*,struct window_pane*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  screen_write_stop (struct screen_write_ctx*) ; 
 int /*<<< orphan*/  window_copy_redraw_lines (struct window_mode_entry*,scalar_t__,int) ; 

__attribute__((used)) static void
window_copy_update_cursor(struct window_mode_entry *wme, u_int cx, u_int cy)
{
	struct window_pane		*wp = wme->wp;
	struct window_copy_mode_data	*data = wme->data;
	struct screen			*s = &data->screen;
	struct screen_write_ctx		 ctx;
	u_int				 old_cx, old_cy;

	old_cx = data->cx; old_cy = data->cy;
	data->cx = cx; data->cy = cy;
	if (old_cx == screen_size_x(s))
		window_copy_redraw_lines(wme, old_cy, 1);
	if (data->cx == screen_size_x(s))
		window_copy_redraw_lines(wme, data->cy, 1);
	else {
		screen_write_start(&ctx, wp, NULL);
		screen_write_cursormove(&ctx, data->cx, data->cy, 0);
		screen_write_stop(&ctx);
	}
}