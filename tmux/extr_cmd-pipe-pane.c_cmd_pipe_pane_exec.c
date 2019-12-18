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
struct window_pane {int pipe_fd; int fd; int /*<<< orphan*/ * pipe_event; int /*<<< orphan*/  pipe_off; TYPE_2__* event; } ;
struct session {int dummy; } ;
struct format_tree {int dummy; } ;
struct TYPE_3__ {struct winlink* wl; struct session* s; struct window_pane* wp; } ;
struct cmdq_item {int /*<<< orphan*/  client; TYPE_1__ target; } ;
struct cmd {struct args* args; } ;
struct client {int dummy; } ;
struct args {scalar_t__ argc; char** argv; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;
struct TYPE_4__ {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int /*<<< orphan*/  EVBUFFER_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  EV_WRITE ; 
 int /*<<< orphan*/  FORMAT_NONE ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  _PATH_BSHELL ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int /*<<< orphan*/  _exit (int) ; 
 int args_has (struct args*,char) ; 
 int /*<<< orphan*/  bufferevent_enable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bufferevent_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct window_pane*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closefrom (int /*<<< orphan*/ ) ; 
 struct client* cmd_find_client (struct cmdq_item*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cmd_pipe_pane_error_callback ; 
 int /*<<< orphan*/  cmd_pipe_pane_read_callback ; 
 int /*<<< orphan*/  cmd_pipe_pane_write_callback ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,int /*<<< orphan*/ ) ; 
 int dup2 (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execl (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  fatalx (char*) ; 
 int fork () ; 
 struct format_tree* format_create (int /*<<< orphan*/ ,struct cmdq_item*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_defaults (struct format_tree*,struct client*,struct session*,struct winlink*,struct window_pane*) ; 
 char* format_expand_time (struct format_tree*,char*) ; 
 int /*<<< orphan*/  format_free (struct format_tree*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_clear_signals (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  server_destroy_pane (struct window_pane*,int) ; 
 int /*<<< orphan*/  server_proc ; 
 int /*<<< orphan*/  setblocking (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ window_pane_destroy_ready (struct window_pane*) ; 

__attribute__((used)) static enum cmd_retval
cmd_pipe_pane_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args		*args = self->args;
	struct client		*c = cmd_find_client(item, NULL, 1);
	struct window_pane	*wp = item->target.wp;
	struct session		*s = item->target.s;
	struct winlink		*wl = item->target.wl;
	char			*cmd;
	int			 old_fd, pipe_fd[2], null_fd, in, out;
	struct format_tree	*ft;
	sigset_t		 set, oldset;

	/* Destroy the old pipe. */
	old_fd = wp->pipe_fd;
	if (wp->pipe_fd != -1) {
		bufferevent_free(wp->pipe_event);
		close(wp->pipe_fd);
		wp->pipe_fd = -1;

		if (window_pane_destroy_ready(wp)) {
			server_destroy_pane(wp, 1);
			return (CMD_RETURN_NORMAL);
		}
	}

	/* If no pipe command, that is enough. */
	if (args->argc == 0 || *args->argv[0] == '\0')
		return (CMD_RETURN_NORMAL);

	/*
	 * With -o, only open the new pipe if there was no previous one. This
	 * allows a pipe to be toggled with a single key, for example:
	 *
	 *	bind ^p pipep -o 'cat >>~/output'
	 */
	if (args_has(self->args, 'o') && old_fd != -1)
		return (CMD_RETURN_NORMAL);

	/* What do we want to do? Neither -I or -O is -O. */
	if (args_has(self->args, 'I')) {
		in = 1;
		out = args_has(self->args, 'O');
	} else {
		in = 0;
		out = 1;
	}

	/* Open the new pipe. */
	if (socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, pipe_fd) != 0) {
		cmdq_error(item, "socketpair error: %s", strerror(errno));
		return (CMD_RETURN_ERROR);
	}

	/* Expand the command. */
	ft = format_create(item->client, item, FORMAT_NONE, 0);
	format_defaults(ft, c, s, wl, wp);
	cmd = format_expand_time(ft, args->argv[0]);
	format_free(ft);

	/* Fork the child. */
	sigfillset(&set);
	sigprocmask(SIG_BLOCK, &set, &oldset);
	switch (fork()) {
	case -1:
		sigprocmask(SIG_SETMASK, &oldset, NULL);
		cmdq_error(item, "fork error: %s", strerror(errno));

		free(cmd);
		return (CMD_RETURN_ERROR);
	case 0:
		/* Child process. */
		proc_clear_signals(server_proc, 1);
		sigprocmask(SIG_SETMASK, &oldset, NULL);
		close(pipe_fd[0]);

		null_fd = open(_PATH_DEVNULL, O_WRONLY, 0);
		if (out) {
			if (dup2(pipe_fd[1], STDIN_FILENO) == -1)
				_exit(1);
		} else {
			if (dup2(null_fd, STDIN_FILENO) == -1)
				_exit(1);
		}
		if (in) {
			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
				_exit(1);
			if (pipe_fd[1] != STDOUT_FILENO)
				close(pipe_fd[1]);
		} else {
			if (dup2(null_fd, STDOUT_FILENO) == -1)
				_exit(1);
		}
		if (dup2(null_fd, STDERR_FILENO) == -1)
			_exit(1);
		closefrom(STDERR_FILENO + 1);

		execl(_PATH_BSHELL, "sh", "-c", cmd, (char *) NULL);
		_exit(1);
	default:
		/* Parent process. */
		sigprocmask(SIG_SETMASK, &oldset, NULL);
		close(pipe_fd[1]);

		wp->pipe_fd = pipe_fd[0];
		if (wp->fd != -1)
			wp->pipe_off = EVBUFFER_LENGTH(wp->event->input);
		else
			wp->pipe_off = 0;

		setblocking(wp->pipe_fd, 0);
		wp->pipe_event = bufferevent_new(wp->pipe_fd,
		    cmd_pipe_pane_read_callback,
		    cmd_pipe_pane_write_callback,
		    cmd_pipe_pane_error_callback,
		    wp);
		if (wp->pipe_event == NULL)
			fatalx("out of memory");
		if (out)
			bufferevent_enable(wp->pipe_event, EV_WRITE);
		if (in)
			bufferevent_enable(wp->pipe_event, EV_READ);

		free(cmd);
		return (CMD_RETURN_NORMAL);
	}
}