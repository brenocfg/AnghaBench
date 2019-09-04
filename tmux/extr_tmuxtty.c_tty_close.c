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
struct tty {int flags; int fd; int /*<<< orphan*/  term; int /*<<< orphan*/  event_out; int /*<<< orphan*/  out; int /*<<< orphan*/  event_in; int /*<<< orphan*/  in; int /*<<< orphan*/  key_timer; } ;

/* Variables and functions */
 int TTY_OPENED ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  evbuffer_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 scalar_t__ event_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_keys_free (struct tty*) ; 
 int /*<<< orphan*/  tty_stop_tty (struct tty*) ; 
 int /*<<< orphan*/  tty_term_free (int /*<<< orphan*/ ) ; 

void
tty_close(struct tty *tty)
{
	if (event_initialized(&tty->key_timer))
		evtimer_del(&tty->key_timer);
	tty_stop_tty(tty);

	if (tty->flags & TTY_OPENED) {
		evbuffer_free(tty->in);
		event_del(&tty->event_in);
		evbuffer_free(tty->out);
		event_del(&tty->event_out);

		tty_term_free(tty->term);
		tty_keys_free(tty);

		tty->flags &= ~TTY_OPENED;
	}

	if (tty->fd != -1) {
		close(tty->fd);
		tty->fd = -1;
	}
}