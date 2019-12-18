#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_3__ {int attr; } ;
struct tty {int cy; int sy; int cx; int sx; scalar_t__ rlower; TYPE_2__* term; TYPE_1__ cell; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int GRID_ATTR_CHARSET ; 
 int TERM_EARLYWRAP ; 
 int /*<<< orphan*/  TTYC_CUP ; 
 int strlen (char const*) ; 
 char* tty_acs_get (struct tty*,int) ; 
 int /*<<< orphan*/  tty_add (struct tty*,...) ; 
 int /*<<< orphan*/  tty_putcode2 (struct tty*,int /*<<< orphan*/ ,scalar_t__,int) ; 

void
tty_putc(struct tty *tty, u_char ch)
{
	const char	*acs;

	if ((tty->term->flags & TERM_EARLYWRAP) &&
	    ch >= 0x20 && ch != 0x7f &&
	    tty->cy == tty->sy - 1 &&
	    tty->cx + 1 >= tty->sx)
		return;

	if (tty->cell.attr & GRID_ATTR_CHARSET) {
		acs = tty_acs_get(tty, ch);
		if (acs != NULL)
			tty_add(tty, acs, strlen(acs));
		else
			tty_add(tty, &ch, 1);
	} else
		tty_add(tty, &ch, 1);

	if (ch >= 0x20 && ch != 0x7f) {
		if (tty->cx >= tty->sx) {
			tty->cx = 1;
			if (tty->cy != tty->rlower)
				tty->cy++;

			/*
			 * On !xenl terminals, force the cursor position to
			 * where we think it should be after a line wrap - this
			 * means it works on sensible terminals as well.
			 */
			if (tty->term->flags & TERM_EARLYWRAP)
				tty_putcode2(tty, TTYC_CUP, tty->cy, tty->cx);
		} else
			tty->cx++;
	}
}