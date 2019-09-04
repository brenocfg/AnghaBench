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
struct tty {int flags; int /*<<< orphan*/  timer; int /*<<< orphan*/ * out; int /*<<< orphan*/  fd; int /*<<< orphan*/  event_out; int /*<<< orphan*/ * in; int /*<<< orphan*/  event_in; int /*<<< orphan*/ * term; int /*<<< orphan*/  term_name; } ;

/* Variables and functions */
 int EV_PERSIST ; 
 int EV_READ ; 
 int EV_WRITE ; 
 int TTY_BLOCK ; 
 int TTY_FREEZE ; 
 int TTY_NOCURSOR ; 
 int TTY_OPENED ; 
 int TTY_TIMER ; 
 void* evbuffer_new () ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct tty*) ; 
 int /*<<< orphan*/  evtimer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tty*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  tty_close (struct tty*) ; 
 int /*<<< orphan*/  tty_keys_build (struct tty*) ; 
 int /*<<< orphan*/  tty_read_callback ; 
 int /*<<< orphan*/  tty_start_tty (struct tty*) ; 
 int /*<<< orphan*/ * tty_term_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  tty_timer_callback ; 
 int /*<<< orphan*/  tty_write_callback ; 

int
tty_open(struct tty *tty, char **cause)
{
	tty->term = tty_term_find(tty->term_name, tty->fd, cause);
	if (tty->term == NULL) {
		tty_close(tty);
		return (-1);
	}
	tty->flags |= TTY_OPENED;

	tty->flags &= ~(TTY_NOCURSOR|TTY_FREEZE|TTY_BLOCK|TTY_TIMER);

	event_set(&tty->event_in, tty->fd, EV_PERSIST|EV_READ,
	    tty_read_callback, tty);
	tty->in = evbuffer_new();
	if (tty->in == NULL)
		fatal("out of memory");

	event_set(&tty->event_out, tty->fd, EV_WRITE, tty_write_callback, tty);
	tty->out = evbuffer_new();
	if (tty->out == NULL)
		fatal("out of memory");

	evtimer_set(&tty->timer, tty_timer_callback, tty);

	tty_start_tty(tty);

	tty_keys_build(tty);

	return (0);
}