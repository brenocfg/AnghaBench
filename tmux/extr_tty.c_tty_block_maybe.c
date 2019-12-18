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
struct tty {int flags; int /*<<< orphan*/  timer; scalar_t__ discarded; int /*<<< orphan*/  out; struct client* client; } ;
struct timeval {int /*<<< orphan*/  tv_usec; } ;
struct client {size_t discarded; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t EVBUFFER_LENGTH (int /*<<< orphan*/ ) ; 
 int TTY_BLOCK ; 
 int /*<<< orphan*/  TTY_BLOCK_INTERVAL ; 
 size_t TTY_BLOCK_START (struct tty*) ; 
 int /*<<< orphan*/  evbuffer_drain (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  evtimer_add (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
tty_block_maybe(struct tty *tty)
{
	struct client	*c = tty->client;
	size_t		 size = EVBUFFER_LENGTH(tty->out);
	struct timeval	 tv = { .tv_usec = TTY_BLOCK_INTERVAL };

	if (size < TTY_BLOCK_START(tty))
		return (0);

	if (tty->flags & TTY_BLOCK)
		return (1);
	tty->flags |= TTY_BLOCK;

	log_debug("%s: can't keep up, %zu discarded", c->name, size);

	evbuffer_drain(tty->out, size);
	c->discarded += size;

	tty->discarded = 0;
	evtimer_add(&tty->timer, &tv);
	return (1);
}