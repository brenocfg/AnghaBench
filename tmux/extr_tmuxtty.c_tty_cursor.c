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
struct tty_term {int dummy; } ;
struct tty {int sx; int cx; int cy; int rlower; scalar_t__ rleft; int rupper; struct tty_term* term; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTYC_CUB ; 
 int /*<<< orphan*/  TTYC_CUB1 ; 
 int /*<<< orphan*/  TTYC_CUD ; 
 int /*<<< orphan*/  TTYC_CUD1 ; 
 int /*<<< orphan*/  TTYC_CUF ; 
 int /*<<< orphan*/  TTYC_CUF1 ; 
 int /*<<< orphan*/  TTYC_CUP ; 
 int /*<<< orphan*/  TTYC_CUU ; 
 int /*<<< orphan*/  TTYC_CUU1 ; 
 int /*<<< orphan*/  TTYC_HOME ; 
 int /*<<< orphan*/  TTYC_HPA ; 
 int /*<<< orphan*/  TTYC_VPA ; 
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/  tty_putc (struct tty*,char) ; 
 int /*<<< orphan*/  tty_putcode (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_putcode1 (struct tty*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tty_putcode2 (struct tty*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ tty_term_has (struct tty_term*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_use_margin (struct tty*) ; 

void
tty_cursor(struct tty *tty, u_int cx, u_int cy)
{
	struct tty_term	*term = tty->term;
	u_int		 thisx, thisy;
	int		 change;

	if (cx > tty->sx - 1)
		cx = tty->sx - 1;

	thisx = tty->cx;
	thisy = tty->cy;

	/* No change. */
	if (cx == thisx && cy == thisy)
		return;

	/* Very end of the line, just use absolute movement. */
	if (thisx > tty->sx - 1)
		goto absolute;

	/* Move to home position (0, 0). */
	if (cx == 0 && cy == 0 && tty_term_has(term, TTYC_HOME)) {
		tty_putcode(tty, TTYC_HOME);
		goto out;
	}

	/* Zero on the next line. */
	if (cx == 0 && cy == thisy + 1 && thisy != tty->rlower &&
	    (!tty_use_margin(tty) || tty->rleft == 0)) {
		tty_putc(tty, '\r');
		tty_putc(tty, '\n');
		goto out;
	}

	/* Moving column or row. */
	if (cy == thisy) {
		/*
		 * Moving column only, row staying the same.
		 */

		/* To left edge. */
		if (cx == 0 && (!tty_use_margin(tty) || tty->rleft == 0)) {
			tty_putc(tty, '\r');
			goto out;
		}

		/* One to the left. */
		if (cx == thisx - 1 && tty_term_has(term, TTYC_CUB1)) {
			tty_putcode(tty, TTYC_CUB1);
			goto out;
		}

		/* One to the right. */
		if (cx == thisx + 1 && tty_term_has(term, TTYC_CUF1)) {
			tty_putcode(tty, TTYC_CUF1);
			goto out;
		}

		/* Calculate difference. */
		change = thisx - cx;	/* +ve left, -ve right */

		/*
		 * Use HPA if change is larger than absolute, otherwise move
		 * the cursor with CUB/CUF.
		 */
		if ((u_int) abs(change) > cx && tty_term_has(term, TTYC_HPA)) {
			tty_putcode1(tty, TTYC_HPA, cx);
			goto out;
		} else if (change > 0 && tty_term_has(term, TTYC_CUB)) {
			if (change == 2 && tty_term_has(term, TTYC_CUB1)) {
				tty_putcode(tty, TTYC_CUB1);
				tty_putcode(tty, TTYC_CUB1);
				goto out;
			}
			tty_putcode1(tty, TTYC_CUB, change);
			goto out;
		} else if (change < 0 && tty_term_has(term, TTYC_CUF)) {
			tty_putcode1(tty, TTYC_CUF, -change);
			goto out;
		}
	} else if (cx == thisx) {
		/*
		 * Moving row only, column staying the same.
		 */

		/* One above. */
		if (thisy != tty->rupper &&
		    cy == thisy - 1 && tty_term_has(term, TTYC_CUU1)) {
			tty_putcode(tty, TTYC_CUU1);
			goto out;
		}

		/* One below. */
		if (thisy != tty->rlower &&
		    cy == thisy + 1 && tty_term_has(term, TTYC_CUD1)) {
			tty_putcode(tty, TTYC_CUD1);
			goto out;
		}

		/* Calculate difference. */
		change = thisy - cy;	/* +ve up, -ve down */

		/*
		 * Try to use VPA if change is larger than absolute or if this
		 * change would cross the scroll region, otherwise use CUU/CUD.
		 */
		if ((u_int) abs(change) > cy ||
		    (change < 0 && cy - change > tty->rlower) ||
		    (change > 0 && cy - change < tty->rupper)) {
			    if (tty_term_has(term, TTYC_VPA)) {
				    tty_putcode1(tty, TTYC_VPA, cy);
				    goto out;
			    }
		} else if (change > 0 && tty_term_has(term, TTYC_CUU)) {
			tty_putcode1(tty, TTYC_CUU, change);
			goto out;
		} else if (change < 0 && tty_term_has(term, TTYC_CUD)) {
			tty_putcode1(tty, TTYC_CUD, -change);
			goto out;
		}
	}

absolute:
	/* Absolute movement. */
	tty_putcode2(tty, TTYC_CUP, cy, cx);

out:
	tty->cx = cx;
	tty->cy = cy;
}