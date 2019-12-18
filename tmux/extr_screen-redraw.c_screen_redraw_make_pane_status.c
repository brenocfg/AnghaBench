#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int ;
struct TYPE_4__ {int /*<<< orphan*/  grid; scalar_t__ mode; } ;
struct window_pane {int id; int sx; TYPE_1__ status_screen; void* status_size; } ;
struct window {int /*<<< orphan*/  options; struct window_pane* active; } ;
struct screen_write_ctx {int dummy; } ;
struct screen {int /*<<< orphan*/  grid; } ;
struct grid_cell {int /*<<< orphan*/  attr; } ;
struct format_tree {int dummy; } ;
struct client {int dummy; } ;

/* Variables and functions */
 int FORMAT_PANE ; 
 int /*<<< orphan*/  FORMAT_STATUS ; 
 int /*<<< orphan*/  GRID_ATTR_CHARSET ; 
 struct format_tree* format_create (struct client*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_defaults (struct format_tree*,struct client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct window_pane*) ; 
 int /*<<< orphan*/  format_draw (struct screen_write_ctx*,struct grid_cell*,void*,char*,int /*<<< orphan*/ *) ; 
 char* format_expand_time (struct format_tree*,char const*) ; 
 int /*<<< orphan*/  format_free (struct format_tree*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ grid_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct screen*,TYPE_1__*,int) ; 
 char* options_get_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  screen_free (struct screen*) ; 
 int /*<<< orphan*/  screen_init (TYPE_1__*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_cursormove (struct screen_write_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_putc (struct screen_write_ctx*,struct grid_cell*,char) ; 
 int /*<<< orphan*/  screen_write_start (struct screen_write_ctx*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  screen_write_stop (struct screen_write_ctx*) ; 
 int /*<<< orphan*/  style_apply (struct grid_cell*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
screen_redraw_make_pane_status(struct client *c, struct window *w,
    struct window_pane *wp)
{
	struct grid_cell	 gc;
	const char		*fmt;
	struct format_tree	*ft;
	char			*expanded;
	u_int			 width, i;
	struct screen_write_ctx	 ctx;
	struct screen		 old;

	if (wp == w->active)
		style_apply(&gc, w->options, "pane-active-border-style");
	else
		style_apply(&gc, w->options, "pane-border-style");

	fmt = options_get_string(w->options, "pane-border-format");

	ft = format_create(c, NULL, FORMAT_PANE|wp->id, FORMAT_STATUS);
	format_defaults(ft, c, NULL, NULL, wp);

	expanded = format_expand_time(ft, fmt);
	if (wp->sx < 4)
		wp->status_size = width = 0;
	else
		wp->status_size = width = wp->sx - 4;

	memcpy(&old, &wp->status_screen, sizeof old);
	screen_init(&wp->status_screen, width, 1, 0);
	wp->status_screen.mode = 0;

	screen_write_start(&ctx, NULL, &wp->status_screen);

	gc.attr |= GRID_ATTR_CHARSET;
	for (i = 0; i < width; i++)
		screen_write_putc(&ctx, &gc, 'q');
	gc.attr &= ~GRID_ATTR_CHARSET;

	screen_write_cursormove(&ctx, 0, 0, 0);
	format_draw(&ctx, &gc, width, expanded, NULL);
	screen_write_stop(&ctx);

	free(expanded);
	format_free(ft);

	if (grid_compare(wp->status_screen.grid, old.grid) == 0) {
		screen_free(&old);
		return (0);
	}
	screen_free(&old);
	return (1);
}