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
struct winlink {int dummy; } ;
struct session {int /*<<< orphan*/  options; int /*<<< orphan*/  curw; } ;
struct TYPE_4__ {int idx; struct session* s; } ;
struct TYPE_3__ {struct winlink* wl; struct session* s; } ;
struct cmdq_item {TYPE_2__ target; TYPE_1__ source; } ;
struct cmd {int /*<<< orphan*/ * entry; struct args* args; } ;
struct args {int dummy; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FIND_QUIET ; 
 int /*<<< orphan*/  CMD_FIND_SESSION ; 
 int /*<<< orphan*/  CMD_FIND_WINDOW ; 
 int /*<<< orphan*/  CMD_FIND_WINDOW_INDEX ; 
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 char* args_get (struct args*,char) ; 
 int args_has (struct args*,char) ; 
 scalar_t__ cmd_find_target (TYPE_2__*,struct cmdq_item*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_move_window_entry ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  recalculate_sizes () ; 
 scalar_t__ server_link_window (struct session*,struct winlink*,struct session*,int,int,int,char**) ; 
 int /*<<< orphan*/  server_status_session (struct session*) ; 
 int /*<<< orphan*/  server_unlink_window (struct session*,struct winlink*) ; 
 int /*<<< orphan*/  session_renumber_windows (struct session*) ; 
 int winlink_shuffle_up (struct session*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum cmd_retval
cmd_move_window_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args	*args = self->args;
	const char	*tflag = args_get(args, 't');
	struct session	*src;
	struct session	*dst;
	struct winlink	*wl;
	char		*cause;
	int		 idx, kflag, dflag, sflag;

	if (args_has(args, 'r')) {
		if (cmd_find_target(&item->target, item, tflag,
		    CMD_FIND_SESSION, CMD_FIND_QUIET) != 0)
			return (CMD_RETURN_ERROR);

		session_renumber_windows(item->target.s);
		recalculate_sizes();
		server_status_session(item->target.s);

		return (CMD_RETURN_NORMAL);
	}
	if (cmd_find_target(&item->target, item, tflag, CMD_FIND_WINDOW,
	    CMD_FIND_WINDOW_INDEX) != 0)
		return (CMD_RETURN_ERROR);
	src = item->source.s;
	dst = item->target.s;
	wl = item->source.wl;
	idx = item->target.idx;

	kflag = args_has(self->args, 'k');
	dflag = args_has(self->args, 'd');
	sflag = args_has(self->args, 's');

	if (args_has(self->args, 'a')) {
		if ((idx = winlink_shuffle_up(dst, dst->curw)) == -1)
			return (CMD_RETURN_ERROR);
	}

	if (server_link_window(src, wl, dst, idx, kflag, !dflag,
	    &cause) != 0) {
		cmdq_error(item, "can't link window: %s", cause);
		free(cause);
		return (CMD_RETURN_ERROR);
	}
	if (self->entry == &cmd_move_window_entry)
		server_unlink_window(src, wl);

	/*
	 * Renumber the winlinks in the src session only, the destination
	 * session already has the correct winlink id to us, either
	 * automatically or specified by -s.
	 */
	if (!sflag && options_get_number(src->options, "renumber-windows"))
		session_renumber_windows(src);

	recalculate_sizes();

	return (CMD_RETURN_NORMAL);
}