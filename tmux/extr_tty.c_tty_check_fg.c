#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct window_pane {int dummy; } ;
struct tty {int term_flags; TYPE_1__* term; } ;
struct grid_cell {int flags; int fg; int attr; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int COLOUR_FLAG_256 ; 
 int COLOUR_FLAG_RGB ; 
 int GRID_ATTR_BRIGHT ; 
 int GRID_FLAG_NOPALETTE ; 
 int TERM_256COLOURS ; 
 int /*<<< orphan*/  TTYC_COLORS ; 
 int /*<<< orphan*/  TTYC_SETRGBF ; 
 int colour_256to16 (int) ; 
 int colour_find_rgb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  colour_split_rgb (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_term_has (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int tty_term_number (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int window_pane_get_palette (struct window_pane*,int) ; 

__attribute__((used)) static void
tty_check_fg(struct tty *tty, struct window_pane *wp, struct grid_cell *gc)
{
	u_char	r, g, b;
	u_int	colours;
	int	c;

	/*
	 * Perform substitution if this pane has a palette. If the bright
	 * attribute is set, use the bright entry in the palette by changing to
	 * the aixterm colour.
	 */
	if (~gc->flags & GRID_FLAG_NOPALETTE) {
		c = gc->fg;
		if (c < 8 && gc->attr & GRID_ATTR_BRIGHT)
			c += 90;
		if ((c = window_pane_get_palette(wp, c)) != -1)
			gc->fg = c;
	}

	/* Is this a 24-bit colour? */
	if (gc->fg & COLOUR_FLAG_RGB) {
		/* Not a 24-bit terminal? Translate to 256-colour palette. */
		if (!tty_term_has(tty->term, TTYC_SETRGBF)) {
			colour_split_rgb(gc->fg, &r, &g, &b);
			gc->fg = colour_find_rgb(r, g, b);
		} else
			return;
	}

	/* How many colours does this terminal have? */
	if ((tty->term->flags|tty->term_flags) & TERM_256COLOURS)
		colours = 256;
	else
		colours = tty_term_number(tty->term, TTYC_COLORS);

	/* Is this a 256-colour colour? */
	if (gc->fg & COLOUR_FLAG_256) {
		/* And not a 256 colour mode? */
		if (colours != 256) {
			gc->fg = colour_256to16(gc->fg);
			if (gc->fg & 8) {
				gc->fg &= 7;
				if (colours >= 16)
					gc->fg += 90;
			}
		}
		return;
	}

	/* Is this an aixterm colour? */
	if (gc->fg >= 90 && gc->fg <= 97 && colours < 16) {
		gc->fg -= 90;
		gc->attr |= GRID_ATTR_BRIGHT;
	}
}