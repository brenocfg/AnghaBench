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
struct tty {int flags; size_t discarded; int /*<<< orphan*/  event_out; int /*<<< orphan*/  out; struct client* client; } ;
struct client {size_t written; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int TTY_BLOCK ; 
 int TTY_STARTED ; 
 int /*<<< orphan*/  evbuffer_add (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int,char const*) ; 
 int tty_log_fd ; 
 int /*<<< orphan*/  write (int,char const*,size_t) ; 

__attribute__((used)) static void
tty_add(struct tty *tty, const char *buf, size_t len)
{
	struct client	*c = tty->client;

	if (tty->flags & TTY_BLOCK) {
		tty->discarded += len;
		return;
	}

	evbuffer_add(tty->out, buf, len);
	log_debug("%s: %.*s", c->name, (int)len, buf);
	c->written += len;

	if (tty_log_fd != -1)
		write(tty_log_fd, buf, len);
	if (tty->flags & TTY_STARTED)
		event_add(&tty->event_out, NULL);
}