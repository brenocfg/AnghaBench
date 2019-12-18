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
struct window_pane {int fd; int sx; int osx; int sy; int pipe_fd; int /*<<< orphan*/  base; int /*<<< orphan*/  status_screen; int /*<<< orphan*/ * screen; void* saved_cy; void* saved_cx; int /*<<< orphan*/ * saved_grid; int /*<<< orphan*/ * pipe_event; scalar_t__ pipe_off; scalar_t__ yoff; scalar_t__ xoff; int /*<<< orphan*/ * layout_cell; int /*<<< orphan*/  modes; int /*<<< orphan*/ * event; int /*<<< orphan*/ * cwd; int /*<<< orphan*/ * shell; int /*<<< orphan*/ * argv; scalar_t__ argc; scalar_t__ id; int /*<<< orphan*/  flags; int /*<<< orphan*/  options; struct window* window; } ;
struct window {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_NAME_MAX ; 
 int /*<<< orphan*/  PANE_STYLECHANGED ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct window_pane*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 void* UINT_MAX ; 
 int /*<<< orphan*/  all_window_panes ; 
 scalar_t__ gethostname (char*,int) ; 
 int /*<<< orphan*/  input_init (struct window_pane*) ; 
 int /*<<< orphan*/  next_window_pane_id ; 
 int /*<<< orphan*/  options_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_init (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  screen_set_title (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  window_pane_tree ; 
 struct window_pane* xcalloc (int,int) ; 

__attribute__((used)) static struct window_pane *
window_pane_create(struct window *w, u_int sx, u_int sy, u_int hlimit)
{
	struct window_pane	*wp;
	char			 host[HOST_NAME_MAX + 1];

	wp = xcalloc(1, sizeof *wp);
	wp->window = w;
	wp->options = options_create(w->options);
	wp->flags = PANE_STYLECHANGED;

	wp->id = next_window_pane_id++;
	RB_INSERT(window_pane_tree, &all_window_panes, wp);

	wp->argc = 0;
	wp->argv = NULL;
	wp->shell = NULL;
	wp->cwd = NULL;

	wp->fd = -1;
	wp->event = NULL;

	TAILQ_INIT(&wp->modes);

	wp->layout_cell = NULL;

	wp->xoff = 0;
	wp->yoff = 0;

	wp->sx = wp->osx = sx;
	wp->sy = wp->osx = sy;

	wp->pipe_fd = -1;
	wp->pipe_off = 0;
	wp->pipe_event = NULL;

	wp->saved_grid = NULL;
	wp->saved_cx = UINT_MAX;
	wp->saved_cy = UINT_MAX;

	screen_init(&wp->base, sx, sy, hlimit);
	wp->screen = &wp->base;

	screen_init(&wp->status_screen, 1, 1, 0);

	if (gethostname(host, sizeof host) == 0)
		screen_set_title(&wp->base, host);

	input_init(wp);

	return (wp);
}