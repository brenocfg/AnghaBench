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
struct window_pane {TYPE_1__* window; int /*<<< orphan*/  searchstr; } ;
struct window_mode_entry {struct window_copy_mode_data* data; struct window_pane* wp; } ;
struct window_copy_mode_data {int /*<<< orphan*/  searchstr; scalar_t__ cy; scalar_t__ oy; struct screen* backing; scalar_t__ cx; } ;
struct screen_write_ctx {int dummy; } ;
struct screen {struct grid* grid; } ;
struct grid {scalar_t__ sy; scalar_t__ hsize; } ;
struct TYPE_2__ {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grid_default_cell ; 
 int options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  screen_free (struct screen*) ; 
 scalar_t__ screen_hsize (struct screen*) ; 
 int /*<<< orphan*/  screen_init (struct screen*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_nputs (struct screen_write_ctx*,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_start (struct screen_write_ctx*,int /*<<< orphan*/ *,struct screen*) ; 
 int /*<<< orphan*/  screen_write_stop (struct screen_write_ctx*) ; 
 int /*<<< orphan*/  screen_write_strlen (char*,int /*<<< orphan*/ ) ; 
 int window_copy_is_lowercase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_copy_move_left (struct screen*,scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  window_copy_move_right (struct screen*,scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  window_copy_redraw_screen (struct window_mode_entry*) ; 
 int window_copy_search_jump (struct window_mode_entry*,struct grid*,struct grid*,scalar_t__,scalar_t__,scalar_t__,int,int,int) ; 
 scalar_t__ window_copy_search_marks (struct window_mode_entry*,struct screen*) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
window_copy_search(struct window_mode_entry *wme, int direction)
{
	struct window_pane		*wp = wme->wp;
	struct window_copy_mode_data	*data = wme->data;
	struct screen			*s = data->backing, ss;
	struct screen_write_ctx		 ctx;
	struct grid			*gd = s->grid;
	u_int				 fx, fy, endline;
	int				 wrapflag, cis, found;

	free(wp->searchstr);
	wp->searchstr = xstrdup(data->searchstr);

	fx = data->cx;
	fy = screen_hsize(data->backing) - data->oy + data->cy;

	screen_init(&ss, screen_write_strlen("%s", data->searchstr), 1, 0);
	screen_write_start(&ctx, NULL, &ss);
	screen_write_nputs(&ctx, -1, &grid_default_cell, "%s", data->searchstr);
	screen_write_stop(&ctx);

	wrapflag = options_get_number(wp->window->options, "wrap-search");
	cis = window_copy_is_lowercase(data->searchstr);

	if (direction) {
		window_copy_move_right(s, &fx, &fy, wrapflag);
		endline = gd->hsize + gd->sy - 1;
	} else {
		window_copy_move_left(s, &fx, &fy, wrapflag);
		endline = 0;
	}
	found = window_copy_search_jump(wme, gd, ss.grid, fx, fy, endline, cis,
	    wrapflag, direction);

	if (window_copy_search_marks(wme, &ss))
		window_copy_redraw_screen(wme);

	screen_free(&ss);
	return (found);
}