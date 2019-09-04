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
struct tty {int fd; int /*<<< orphan*/ * mouse_drag_release; int /*<<< orphan*/ * mouse_drag_update; scalar_t__ mouse_drag_flag; int /*<<< orphan*/  flags; int /*<<< orphan*/  term; int /*<<< orphan*/  tio; int /*<<< orphan*/  event_in; struct client* client; } ;
struct termios {int c_iflag; int c_oflag; int c_lflag; int* c_cc; } ;
struct client {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ECHO ; 
 int ECHOCTL ; 
 int ECHOE ; 
 int ECHOKE ; 
 int ECHONL ; 
 int ECHOPRT ; 
 int ICANON ; 
 int ICRNL ; 
 int IEXTEN ; 
 int IGNBRK ; 
 int IGNCR ; 
 int IMAXBEL ; 
 int INLCR ; 
 int ISIG ; 
 int ISTRIP ; 
 int IXOFF ; 
 int IXON ; 
 int OCRNL ; 
 int ONLCR ; 
 int ONLRET ; 
 int OPOST ; 
 int /*<<< orphan*/  TCIOFLUSH ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  TTYC_CLEAR ; 
 int /*<<< orphan*/  TTYC_CNORM ; 
 int /*<<< orphan*/  TTYC_ENACS ; 
 int /*<<< orphan*/  TTYC_KMOUS ; 
 int /*<<< orphan*/  TTYC_SMCUP ; 
 int /*<<< orphan*/  TTYC_SMKX ; 
 int /*<<< orphan*/  TTYC_XT ; 
 int /*<<< orphan*/  TTY_FOCUS ; 
 int /*<<< orphan*/  TTY_STARTED ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_options ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct termios*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setblocking (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcflush (int,int /*<<< orphan*/ ) ; 
 scalar_t__ tcgetattr (int,int /*<<< orphan*/ *) ; 
 scalar_t__ tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 
 scalar_t__ tty_acs_needed (struct tty*) ; 
 int /*<<< orphan*/  tty_force_cursor_colour (struct tty*,char*) ; 
 int /*<<< orphan*/  tty_invalidate (struct tty*) ; 
 int /*<<< orphan*/  tty_putcode (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_puts (struct tty*,char*) ; 
 scalar_t__ tty_term_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_term_has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tty_start_tty(struct tty *tty)
{
	struct client	*c = tty->client;
	struct termios	 tio;

	if (tty->fd != -1 && tcgetattr(tty->fd, &tty->tio) == 0) {
		setblocking(tty->fd, 0);
		event_add(&tty->event_in, NULL);

		memcpy(&tio, &tty->tio, sizeof tio);
		tio.c_iflag &= ~(IXON|IXOFF|ICRNL|INLCR|IGNCR|IMAXBEL|ISTRIP);
		tio.c_iflag |= IGNBRK;
		tio.c_oflag &= ~(OPOST|ONLCR|OCRNL|ONLRET);
		tio.c_lflag &= ~(IEXTEN|ICANON|ECHO|ECHOE|ECHONL|ECHOCTL|
		    ECHOPRT|ECHOKE|ISIG);
		tio.c_cc[VMIN] = 1;
		tio.c_cc[VTIME] = 0;
		if (tcsetattr(tty->fd, TCSANOW, &tio) == 0)
			tcflush(tty->fd, TCIOFLUSH);
	}

	tty_putcode(tty, TTYC_SMCUP);

	tty_putcode(tty, TTYC_SMKX);
	tty_putcode(tty, TTYC_CLEAR);

	if (tty_acs_needed(tty)) {
		log_debug("%s: using capabilities for ACS", c->name);
		tty_putcode(tty, TTYC_ENACS);
	} else
		log_debug("%s: using UTF-8 for ACS", c->name);

	tty_putcode(tty, TTYC_CNORM);
	if (tty_term_has(tty->term, TTYC_KMOUS))
		tty_puts(tty, "\033[?1000l\033[?1002l\033[?1006l\033[?1005l");

	if (tty_term_flag(tty->term, TTYC_XT)) {
		if (options_get_number(global_options, "focus-events")) {
			tty->flags |= TTY_FOCUS;
			tty_puts(tty, "\033[?1004h");
		}
		tty_puts(tty, "\033[c");
	}

	tty->flags |= TTY_STARTED;
	tty_invalidate(tty);

	tty_force_cursor_colour(tty, "");

	tty->mouse_drag_flag = 0;
	tty->mouse_drag_update = NULL;
	tty->mouse_drag_release = NULL;
}