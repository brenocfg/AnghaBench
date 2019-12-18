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
typedef  scalar_t__ u_int ;
struct window {scalar_t__ sx; scalar_t__ sy; } ;
struct tty {scalar_t__ oox; scalar_t__ ooy; scalar_t__ osx; scalar_t__ osy; } ;
struct cmdq_item {int dummy; } ;
struct cmd {struct args* args; } ;
struct client {scalar_t__ pan_ox; scalar_t__ pan_oy; int flags; struct tty tty; TYPE_2__* session; struct window* pan_window; } ;
struct args {scalar_t__ argc; int /*<<< orphan*/ * argv; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;
struct TYPE_4__ {TYPE_1__* curw; } ;
struct TYPE_3__ {struct window* window; } ;

/* Variables and functions */
 int CLIENT_CONTROL ; 
 int CLIENT_CONTROL_NOOUTPUT ; 
 int CLIENT_SIZECHANGED ; 
 int CLIENT_STATUSFORCE ; 
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  TTYC_MS ; 
 scalar_t__ WINDOW_MAXIMUM ; 
 scalar_t__ WINDOW_MINIMUM ; 
 char* args_get (struct args*,float) ; 
 scalar_t__ args_has (struct args*,char) ; 
 struct client* cmd_find_client (struct cmdq_item*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  recalculate_sizes () ; 
 int /*<<< orphan*/  server_redraw_client (struct client*) ; 
 int /*<<< orphan*/  server_status_client (struct client*) ; 
 int sscanf (char const*,char*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ strtonum (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  tty_putcode_ptr2 (struct tty*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  tty_set_size (struct tty*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tty_update_client_offset (struct client*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static enum cmd_retval
cmd_refresh_client_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args	*args = self->args;
	struct client	*c;
	struct tty	*tty;
	struct window	*w;
	const char	*size, *errstr;
	char		*copy, *next, *s;
	u_int		 x, y, adjust;

	if ((c = cmd_find_client(item, args_get(args, 't'), 0)) == NULL)
		return (CMD_RETURN_ERROR);
	tty = &c->tty;

	if (args_has(args, 'c') ||
	    args_has(args, 'L') ||
	    args_has(args, 'R') ||
	    args_has(args, 'U') ||
	    args_has(args, 'D'))
	{
		if (args->argc == 0)
			adjust = 1;
		else {
			adjust = strtonum(args->argv[0], 1, INT_MAX, &errstr);
			if (errstr != NULL) {
				cmdq_error(item, "adjustment %s", errstr);
				return (CMD_RETURN_ERROR);
			}
		}

		if (args_has(args, 'c'))
		    c->pan_window = NULL;
		else {
			w = c->session->curw->window;
			if (c->pan_window != w) {
				c->pan_window = w;
				c->pan_ox = tty->oox;
				c->pan_oy = tty->ooy;
			}
			if (args_has(args, 'L')) {
				if (c->pan_ox > adjust)
					c->pan_ox -= adjust;
				else
					c->pan_ox = 0;
			} else if (args_has(args, 'R')) {
				c->pan_ox += adjust;
				if (c->pan_ox > w->sx - tty->osx)
					c->pan_ox = w->sx - tty->osx;
			} else if (args_has(args, 'U')) {
				if (c->pan_oy > adjust)
					c->pan_oy -= adjust;
				else
					c->pan_oy = 0;
			} else if (args_has(args, 'D')) {
				c->pan_oy += adjust;
				if (c->pan_oy > w->sy - tty->osy)
					c->pan_oy = w->sy - tty->osy;
			}
		}
		tty_update_client_offset(c);
		server_redraw_client(c);
		return (CMD_RETURN_NORMAL);
	}

	if (args_has(args, 'l')) {
		if (c->session != NULL)
			tty_putcode_ptr2(&c->tty, TTYC_MS, "", "?");
		return (CMD_RETURN_NORMAL);
	}

	if (args_has(args, 'C') || args_has(args, 'F')) {
		if (args_has(args, 'C')) {
			if (!(c->flags & CLIENT_CONTROL)) {
				cmdq_error(item, "not a control client");
				return (CMD_RETURN_ERROR);
			}
			size = args_get(args, 'C');
			if (sscanf(size, "%u,%u", &x, &y) != 2 &&
			    sscanf(size, "%ux%u", &x, &y) != 2) {
				cmdq_error(item, "bad size argument");
				return (CMD_RETURN_ERROR);
			}
			if (x < WINDOW_MINIMUM || x > WINDOW_MAXIMUM ||
			    y < WINDOW_MINIMUM || y > WINDOW_MAXIMUM) {
				cmdq_error(item, "size too small or too big");
				return (CMD_RETURN_ERROR);
			}
			tty_set_size(&c->tty, x, y);
			c->flags |= CLIENT_SIZECHANGED;
			recalculate_sizes();
		}
		if (args_has(args, 'F')) {
			if (!(c->flags & CLIENT_CONTROL)) {
				cmdq_error(item, "not a control client");
				return (CMD_RETURN_ERROR);
			}
			s = copy = xstrdup(args_get(args, 'F'));
			while ((next = strsep(&s, ",")) != NULL) {
				/* Unknown flags are ignored. */
				if (strcmp(next, "no-output") == 0)
					c->flags |= CLIENT_CONTROL_NOOUTPUT;
			}
			free(copy);
		}
		return (CMD_RETURN_NORMAL);
	}

	if (args_has(args, 'S')) {
		c->flags |= CLIENT_STATUSFORCE;
		server_status_client(c);
	} else {
		c->flags |= CLIENT_STATUSFORCE;
		server_redraw_client(c);
	}
	return (CMD_RETURN_NORMAL);
}