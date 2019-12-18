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
struct window_pane {scalar_t__ xoff; scalar_t__ sx; scalar_t__ yoff; scalar_t__ sy; struct window* window; } ;
struct window {struct window_pane* active; } ;
struct tty {int dummy; } ;
struct session {struct options* options; } ;
struct screen_redraw_ctx {scalar_t__ ox; scalar_t__ sx; scalar_t__ oy; scalar_t__ sy; int statuslines; scalar_t__ statustop; struct client* c; } ;
struct options {int dummy; } ;
struct grid_cell {int bg; int fg; int /*<<< orphan*/  flags; } ;
struct client {struct session* session; struct tty tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRID_FLAG_NOPALETTE ; 
 int /*<<< orphan*/  fatalx (char*) ; 
 int /*<<< orphan*/  grid_default_cell ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,int /*<<< orphan*/ *,int) ; 
 int options_get_number (struct options*,char*) ; 
 int /*<<< orphan*/  tty_attributes (struct tty*,struct grid_cell*,struct window_pane*) ; 
 int /*<<< orphan*/  tty_cursor (struct tty*,int,int) ; 
 int /*<<< orphan*/  tty_putc (struct tty*,char) ; 
 int /*<<< orphan*/  tty_puts (struct tty*,char*) ; 
 scalar_t__*** window_clock_table ; 
 scalar_t__ window_pane_index (struct window_pane*,int*) ; 
 size_t xsnprintf (char*,int,char*,int,...) ; 

__attribute__((used)) static void
cmd_display_panes_draw_pane(struct screen_redraw_ctx *ctx,
    struct window_pane *wp)
{
	struct client		*c = ctx->c;
	struct tty		*tty = &c->tty;
	struct session		*s = c->session;
	struct options		*oo = s->options;
	struct window		*w = wp->window;
	struct grid_cell	 gc;
	u_int			 idx, px, py, i, j, xoff, yoff, sx, sy;
	int			 colour, active_colour;
	char			 buf[16], *ptr;
	size_t			 len;

	if (wp->xoff + wp->sx <= ctx->ox ||
	    wp->xoff >= ctx->ox + ctx->sx ||
	    wp->yoff + wp->sy <= ctx->oy ||
	    wp->yoff >= ctx->oy + ctx->sy)
		return;

	if (wp->xoff >= ctx->ox && wp->xoff + wp->sx <= ctx->ox + ctx->sx) {
		/* All visible. */
		xoff = wp->xoff - ctx->ox;
		sx = wp->sx;
	} else if (wp->xoff < ctx->ox &&
	    wp->xoff + wp->sx > ctx->ox + ctx->sx) {
		/* Both left and right not visible. */
		xoff = 0;
		sx = ctx->sx;
	} else if (wp->xoff < ctx->ox) {
		/* Left not visible. */
		xoff = 0;
		sx = wp->sx - (ctx->ox - wp->xoff);
	} else {
		/* Right not visible. */
		xoff = wp->xoff - ctx->ox;
		sx = wp->sx - xoff;
	}
	if (wp->yoff >= ctx->oy && wp->yoff + wp->sy <= ctx->oy + ctx->sy) {
		/* All visible. */
		yoff = wp->yoff - ctx->oy;
		sy = wp->sy;
	} else if (wp->yoff < ctx->oy &&
	    wp->yoff + wp->sy > ctx->oy + ctx->sy) {
		/* Both top and bottom not visible. */
		yoff = 0;
		sy = ctx->sy;
	} else if (wp->yoff < ctx->oy) {
		/* Top not visible. */
		yoff = 0;
		sy = wp->sy - (ctx->oy - wp->yoff);
	} else {
		/* Bottom not visible. */
		yoff = wp->yoff - ctx->oy;
		sy = wp->sy - yoff;
	}

	if (ctx->statustop)
		yoff += ctx->statuslines;
	px = sx / 2;
	py = sy / 2;

	if (window_pane_index(wp, &idx) != 0)
		fatalx("index not found");
	len = xsnprintf(buf, sizeof buf, "%u", idx);

	if (sx < len)
		return;
	colour = options_get_number(oo, "display-panes-colour");
	active_colour = options_get_number(oo, "display-panes-active-colour");

	if (sx < len * 6 || sy < 5) {
		tty_cursor(tty, xoff + px - len / 2, yoff + py);
		goto draw_text;
	}

	px -= len * 3;
	py -= 2;

	memcpy(&gc, &grid_default_cell, sizeof gc);
	if (w->active == wp)
		gc.bg = active_colour;
	else
		gc.bg = colour;
	gc.flags |= GRID_FLAG_NOPALETTE;

	tty_attributes(tty, &gc, wp);
	for (ptr = buf; *ptr != '\0'; ptr++) {
		if (*ptr < '0' || *ptr > '9')
			continue;
		idx = *ptr - '0';

		for (j = 0; j < 5; j++) {
			for (i = px; i < px + 5; i++) {
				tty_cursor(tty, xoff + i, yoff + py + j);
				if (window_clock_table[idx][j][i - px])
					tty_putc(tty, ' ');
			}
		}
		px += 6;
	}

	len = xsnprintf(buf, sizeof buf, "%ux%u", wp->sx, wp->sy);
	if (sx < len || sy < 6)
		return;
	tty_cursor(tty, xoff + sx - len, yoff);

draw_text:
	memcpy(&gc, &grid_default_cell, sizeof gc);
	if (w->active == wp)
		gc.fg = active_colour;
	else
		gc.fg = colour;
	gc.flags |= GRID_FLAG_NOPALETTE;

	tty_attributes(tty, &gc, wp);
	tty_puts(tty, buf);

	tty_cursor(tty, 0, 0);
}