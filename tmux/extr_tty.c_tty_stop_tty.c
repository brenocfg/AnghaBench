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
struct winsize {scalar_t__ ws_row; } ;
struct tty {int flags; scalar_t__ cstyle; int mode; int /*<<< orphan*/  fd; int /*<<< orphan*/  term; int /*<<< orphan*/  tio; int /*<<< orphan*/  event_out; int /*<<< orphan*/  event_in; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int MODE_BRACKETPASTE ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  TTYC_CLEAR ; 
 int /*<<< orphan*/  TTYC_CNORM ; 
 int /*<<< orphan*/  TTYC_CR ; 
 int /*<<< orphan*/  TTYC_CSR ; 
 int /*<<< orphan*/  TTYC_KMOUS ; 
 int /*<<< orphan*/  TTYC_RMACS ; 
 int /*<<< orphan*/  TTYC_RMCUP ; 
 int /*<<< orphan*/  TTYC_RMKX ; 
 int /*<<< orphan*/  TTYC_SE ; 
 int /*<<< orphan*/  TTYC_SGR0 ; 
 int /*<<< orphan*/  TTYC_SS ; 
 int /*<<< orphan*/  TTYC_XT ; 
 int TTY_BLOCK ; 
 int TTY_FOCUS ; 
 int TTY_STARTED ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 int /*<<< orphan*/  setblocking (int /*<<< orphan*/ ,int) ; 
 int tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ tty_acs_needed (struct tty*) ; 
 int /*<<< orphan*/  tty_raw (struct tty*,char*) ; 
 scalar_t__ tty_term_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_term_has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* tty_term_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* tty_term_string1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* tty_term_string2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tty_use_margin (struct tty*) ; 

void
tty_stop_tty(struct tty *tty)
{
	struct winsize	ws;

	if (!(tty->flags & TTY_STARTED))
		return;
	tty->flags &= ~TTY_STARTED;

	event_del(&tty->timer);
	tty->flags &= ~TTY_BLOCK;

	event_del(&tty->event_in);
	event_del(&tty->event_out);

	/*
	 * Be flexible about error handling and try not kill the server just
	 * because the fd is invalid. Things like ssh -t can easily leave us
	 * with a dead tty.
	 */
	if (ioctl(tty->fd, TIOCGWINSZ, &ws) == -1)
		return;
	if (tcsetattr(tty->fd, TCSANOW, &tty->tio) == -1)
		return;

	tty_raw(tty, tty_term_string2(tty->term, TTYC_CSR, 0, ws.ws_row - 1));
	if (tty_acs_needed(tty))
		tty_raw(tty, tty_term_string(tty->term, TTYC_RMACS));
	tty_raw(tty, tty_term_string(tty->term, TTYC_SGR0));
	tty_raw(tty, tty_term_string(tty->term, TTYC_RMKX));
	tty_raw(tty, tty_term_string(tty->term, TTYC_CLEAR));
	if (tty_term_has(tty->term, TTYC_SS) && tty->cstyle != 0) {
		if (tty_term_has(tty->term, TTYC_SE))
			tty_raw(tty, tty_term_string(tty->term, TTYC_SE));
		else
			tty_raw(tty, tty_term_string1(tty->term, TTYC_SS, 0));
	}
	if (tty->mode & MODE_BRACKETPASTE)
		tty_raw(tty, "\033[?2004l");
	tty_raw(tty, tty_term_string(tty->term, TTYC_CR));

	tty_raw(tty, tty_term_string(tty->term, TTYC_CNORM));
	if (tty_term_has(tty->term, TTYC_KMOUS))
		tty_raw(tty, "\033[?1000l\033[?1002l\033[?1006l\033[?1005l");

	if (tty_term_flag(tty->term, TTYC_XT)) {
		if (tty->flags & TTY_FOCUS) {
			tty->flags &= ~TTY_FOCUS;
			tty_raw(tty, "\033[?1004l");
		}
	}

	if (tty_use_margin(tty))
		tty_raw(tty, "\033[?69l"); /* DECLRMM */
	tty_raw(tty, tty_term_string(tty->term, TTYC_RMCUP));

	setblocking(tty->fd, 1);
}