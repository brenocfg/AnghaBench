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
typedef  char u_char ;
struct tty {int mouse_last_x; int mouse_last_y; int mouse_last_b; struct client* client; } ;
struct mouse_event {int lx; int x; int ly; int y; int lb; int b; char sgr_type; int sgr_b; } ;
struct client {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int,char const*) ; 

__attribute__((used)) static int
tty_keys_mouse(struct tty *tty, const char *buf, size_t len, size_t *size,
    struct mouse_event *m)
{
	struct client	*c = tty->client;
	u_int		 i, x, y, b, sgr_b;
	u_char		 sgr_type, ch;

	/*
	 * Standard mouse sequences are \033[M followed by three characters
	 * indicating button, X and Y, all based at 32 with 1,1 top-left.
	 *
	 * UTF-8 mouse sequences are similar but the three are expressed as
	 * UTF-8 characters.
	 *
	 * SGR extended mouse sequences are \033[< followed by three numbers in
	 * decimal and separated by semicolons indicating button, X and Y. A
	 * trailing 'M' is click or scroll and trailing 'm' release. All are
	 * based at 0 with 1,1 top-left.
	 */

	*size = 0;
	x = y = b = sgr_b = 0;
	sgr_type = ' ';

	/* First two bytes are always \033[. */
	if (buf[0] != '\033')
		return (-1);
	if (len == 1)
		return (1);
	if (buf[1] != '[')
		return (-1);
	if (len == 2)
		return (1);

	/*
	 * Third byte is M in old standard (and UTF-8 extension which we do not
	 * support), < in SGR extension.
	 */
	if (buf[2] == 'M') {
		/* Read the three inputs. */
		*size = 3;
		for (i = 0; i < 3; i++) {
			if (len <= *size)
				return (1);
			ch = (u_char)buf[(*size)++];
			if (i == 0)
				b = ch;
			else if (i == 1)
				x = ch;
			else
				y = ch;
		}
		log_debug("%s: mouse input: %.*s", c->name, (int)*size, buf);

		/* Check and return the mouse input. */
		if (b < 32)
			return (-1);
		b -= 32;
		if (x >= 33)
			x -= 33;
		else
			x = 256 - x;
		if (y >= 33)
			y -= 33;
		else
			y = 256 - y;
	} else if (buf[2] == '<') {
		/* Read the three inputs. */
		*size = 3;
		while (1) {
			if (len <= *size)
				return (1);
			ch = (u_char)buf[(*size)++];
			if (ch == ';')
				break;
			if (ch < '0' || ch > '9')
				return (-1);
			sgr_b = 10 * sgr_b + (ch - '0');
		}
		while (1) {
			if (len <= *size)
				return (1);
			ch = (u_char)buf[(*size)++];
			if (ch == ';')
				break;
			if (ch < '0' || ch > '9')
				return (-1);
			x = 10 * x + (ch - '0');
		}
		while (1) {
			if (len <= *size)
				return (1);
			ch = (u_char)buf[(*size)++];
			if (ch == 'M' || ch == 'm')
				break;
			if (ch < '0' || ch > '9')
				return (-1);
			y = 10 * y + (ch - '0');
		}
		log_debug("%s: mouse input (SGR): %.*s", c->name, (int)*size,
		    buf);

		/* Check and return the mouse input. */
		if (x < 1 || y < 1)
			return (-1);
		x--;
		y--;
		b = sgr_b;

		/* Type is M for press, m for release. */
		sgr_type = ch;
		if (sgr_type == 'm')
			b |= 3;

		/*
		 * Some terminals (like PuTTY 0.63) mistakenly send
		 * button-release events for scroll-wheel button-press event.
		 * Discard it before it reaches any program running inside
		 * tmux.
		 */
		if (sgr_type == 'm' && (sgr_b & 64))
		    return (-2);
	} else
		return (-1);

	/* Fill mouse event. */
	m->lx = tty->mouse_last_x;
	m->x = x;
	m->ly = tty->mouse_last_y;
	m->y = y;
	m->lb = tty->mouse_last_b;
	m->b = b;
	m->sgr_type = sgr_type;
	m->sgr_b = sgr_b;

	/* Update last mouse state. */
	tty->mouse_last_x = x;
	tty->mouse_last_y = y;
	tty->mouse_last_b = b;

	return (0);
}