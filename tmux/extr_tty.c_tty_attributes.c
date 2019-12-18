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
struct window_pane {int flags; scalar_t__ id; } ;
struct grid_cell {scalar_t__ attr; scalar_t__ fg; scalar_t__ bg; scalar_t__ us; } ;
struct tty {int last_wp; int /*<<< orphan*/  term; struct grid_cell last_cell; struct grid_cell cell; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOUR_DEFAULT (scalar_t__) ; 
 int GRID_ATTR_ALL_UNDERSCORE ; 
 int GRID_ATTR_BLINK ; 
 int GRID_ATTR_BRIGHT ; 
 int GRID_ATTR_CHARSET ; 
 int GRID_ATTR_DIM ; 
 int GRID_ATTR_HIDDEN ; 
 int GRID_ATTR_ITALICS ; 
 int GRID_ATTR_OVERLINE ; 
 int GRID_ATTR_REVERSE ; 
 int GRID_ATTR_STRIKETHROUGH ; 
 int GRID_ATTR_UNDERSCORE ; 
 int GRID_ATTR_UNDERSCORE_2 ; 
 int GRID_ATTR_UNDERSCORE_3 ; 
 int GRID_ATTR_UNDERSCORE_4 ; 
 int GRID_ATTR_UNDERSCORE_5 ; 
 int PANE_STYLECHANGED ; 
 int /*<<< orphan*/  TTYC_BLINK ; 
 int /*<<< orphan*/  TTYC_BOLD ; 
 int /*<<< orphan*/  TTYC_DIM ; 
 int /*<<< orphan*/  TTYC_INVIS ; 
 int /*<<< orphan*/  TTYC_REV ; 
 int /*<<< orphan*/  TTYC_SETAB ; 
 int /*<<< orphan*/  TTYC_SMACS ; 
 int /*<<< orphan*/  TTYC_SMOL ; 
 int /*<<< orphan*/  TTYC_SMSO ; 
 int /*<<< orphan*/  TTYC_SMUL ; 
 int /*<<< orphan*/  TTYC_SMULX ; 
 int /*<<< orphan*/  TTYC_SMXX ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,struct grid_cell const*,int) ; 
 scalar_t__ tty_acs_needed (struct tty*) ; 
 int /*<<< orphan*/  tty_check_bg (struct tty*,struct window_pane*,struct grid_cell*) ; 
 int /*<<< orphan*/  tty_check_fg (struct tty*,struct window_pane*,struct grid_cell*) ; 
 int /*<<< orphan*/  tty_check_us (struct tty*,struct window_pane*,struct grid_cell*) ; 
 int /*<<< orphan*/  tty_colours (struct tty*,struct grid_cell*) ; 
 int /*<<< orphan*/  tty_default_colours (struct grid_cell*,struct window_pane*) ; 
 int /*<<< orphan*/  tty_putcode (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_putcode1 (struct tty*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tty_reset (struct tty*) ; 
 int /*<<< orphan*/  tty_set_italics (struct tty*) ; 
 scalar_t__ tty_term_has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tty_attributes(struct tty *tty, const struct grid_cell *gc,
    struct window_pane *wp)
{
	struct grid_cell	*tc = &tty->cell, gc2;
	int			 changed;

	/* Ignore cell if it is the same as the last one. */
	if (wp != NULL &&
	    (int)wp->id == tty->last_wp &&
	    ~(wp->flags & PANE_STYLECHANGED) &&
	    gc->attr == tty->last_cell.attr &&
	    gc->fg == tty->last_cell.fg &&
	    gc->bg == tty->last_cell.bg &&
	    gc->us == tty->last_cell.us)
		return;
	tty->last_wp = (wp != NULL ? (int)wp->id : -1);
	memcpy(&tty->last_cell, gc, sizeof tty->last_cell);

	/* Copy cell and update default colours. */
	memcpy(&gc2, gc, sizeof gc2);
	if (wp != NULL)
		tty_default_colours(&gc2, wp);

	/*
	 * If no setab, try to use the reverse attribute as a best-effort for a
	 * non-default background. This is a bit of a hack but it doesn't do
	 * any serious harm and makes a couple of applications happier.
	 */
	if (!tty_term_has(tty->term, TTYC_SETAB)) {
		if (gc2.attr & GRID_ATTR_REVERSE) {
			if (gc2.fg != 7 && !COLOUR_DEFAULT(gc2.fg))
				gc2.attr &= ~GRID_ATTR_REVERSE;
		} else {
			if (gc2.bg != 0 && !COLOUR_DEFAULT(gc2.bg))
				gc2.attr |= GRID_ATTR_REVERSE;
		}
	}

	/* Fix up the colours if necessary. */
	tty_check_fg(tty, wp, &gc2);
	tty_check_bg(tty, wp, &gc2);
	tty_check_us(tty, wp, &gc2);

	/*
	 * If any bits are being cleared or the underline colour is now default,
	 * reset everything.
	 */
	if ((tc->attr & ~gc2.attr) || (tc->us != gc2.us && gc2.us == 0))
		tty_reset(tty);

	/*
	 * Set the colours. This may call tty_reset() (so it comes next) and
	 * may add to (NOT remove) the desired attributes.
	 */
	tty_colours(tty, &gc2);

	/* Filter out attribute bits already set. */
	changed = gc2.attr & ~tc->attr;
	tc->attr = gc2.attr;

	/* Set the attributes. */
	if (changed & GRID_ATTR_BRIGHT)
		tty_putcode(tty, TTYC_BOLD);
	if (changed & GRID_ATTR_DIM)
		tty_putcode(tty, TTYC_DIM);
	if (changed & GRID_ATTR_ITALICS)
		tty_set_italics(tty);
	if (changed & GRID_ATTR_ALL_UNDERSCORE) {
		if ((changed & GRID_ATTR_UNDERSCORE) ||
		    !tty_term_has(tty->term, TTYC_SMULX))
			tty_putcode(tty, TTYC_SMUL);
		else if (changed & GRID_ATTR_UNDERSCORE_2)
			tty_putcode1(tty, TTYC_SMULX, 2);
		else if (changed & GRID_ATTR_UNDERSCORE_3)
			tty_putcode1(tty, TTYC_SMULX, 3);
		else if (changed & GRID_ATTR_UNDERSCORE_4)
			tty_putcode1(tty, TTYC_SMULX, 4);
		else if (changed & GRID_ATTR_UNDERSCORE_5)
			tty_putcode1(tty, TTYC_SMULX, 5);
	}
	if (changed & GRID_ATTR_BLINK)
		tty_putcode(tty, TTYC_BLINK);
	if (changed & GRID_ATTR_REVERSE) {
		if (tty_term_has(tty->term, TTYC_REV))
			tty_putcode(tty, TTYC_REV);
		else if (tty_term_has(tty->term, TTYC_SMSO))
			tty_putcode(tty, TTYC_SMSO);
	}
	if (changed & GRID_ATTR_HIDDEN)
		tty_putcode(tty, TTYC_INVIS);
	if (changed & GRID_ATTR_STRIKETHROUGH)
		tty_putcode(tty, TTYC_SMXX);
	if (changed & GRID_ATTR_OVERLINE)
		tty_putcode(tty, TTYC_SMOL);
	if ((changed & GRID_ATTR_CHARSET) && tty_acs_needed(tty))
		tty_putcode(tty, TTYC_SMACS);
}