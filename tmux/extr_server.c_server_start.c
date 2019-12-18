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
struct tmuxproc {int dummy; } ;
struct event_base {int dummy; } ;
struct client {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  CLIENT_EXIT ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  all_window_panes ; 
 int /*<<< orphan*/  clients ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  cmdq_append (struct client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_get_error (char*) ; 
 scalar_t__ daemon (int,int /*<<< orphan*/ ) ; 
 scalar_t__ event_reinit (struct event_base*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  fatalx (char*) ; 
 int fork () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  job_kill_all () ; 
 int /*<<< orphan*/  key_bindings_init () ; 
 int log_get_level () ; 
 scalar_t__ pledge (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_clear_signals (struct tmuxproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_set_signals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_start (char*) ; 
 int /*<<< orphan*/  server_add_accept (int /*<<< orphan*/ ) ; 
 struct client* server_client_create (int) ; 
 int server_create_socket (char**) ; 
 int server_fd ; 
 int /*<<< orphan*/  server_loop ; 
 int /*<<< orphan*/  server_proc ; 
 int /*<<< orphan*/  server_signal ; 
 int /*<<< orphan*/  server_update_socket () ; 
 int /*<<< orphan*/  sessions ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  status_prompt_save_history () ; 
 int /*<<< orphan*/  tty_create_log () ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  windows ; 

int
server_start(struct tmuxproc *client, struct event_base *base, int lockfd,
    char *lockfile)
{
	int		 pair[2];
	sigset_t	 set, oldset;
	struct client	*c;
	char		*cause = NULL;

	if (socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, pair) != 0)
		fatal("socketpair failed");

	sigfillset(&set);
	sigprocmask(SIG_BLOCK, &set, &oldset);
	switch (fork()) {
	case -1:
		fatal("fork failed");
	case 0:
		break;
	default:
		sigprocmask(SIG_SETMASK, &oldset, NULL);
		close(pair[1]);
		return (pair[0]);
	}
	close(pair[0]);
	if (daemon(1, 0) != 0)
		fatal("daemon failed");
	proc_clear_signals(client, 0);
	if (event_reinit(base) != 0)
		fatalx("event_reinit failed");
	server_proc = proc_start("server");
	proc_set_signals(server_proc, server_signal);
	sigprocmask(SIG_SETMASK, &oldset, NULL);

	if (log_get_level() > 1)
		tty_create_log();
	if (pledge("stdio rpath wpath cpath fattr unix getpw recvfd proc exec "
	    "tty ps", NULL) != 0)
		fatal("pledge failed");

	RB_INIT(&windows);
	RB_INIT(&all_window_panes);
	TAILQ_INIT(&clients);
	RB_INIT(&sessions);
	key_bindings_init();

	gettimeofday(&start_time, NULL);

	server_fd = server_create_socket(&cause);
	if (server_fd != -1)
		server_update_socket();
	c = server_client_create(pair[1]);

	if (lockfd >= 0) {
		unlink(lockfile);
		free(lockfile);
		close(lockfd);
	}

	if (cause != NULL) {
		cmdq_append(c, cmdq_get_error(cause));
		free(cause);
		c->flags |= CLIENT_EXIT;
	}

	server_add_accept(0);
	proc_loop(server_proc, server_loop);

	job_kill_all();
	status_prompt_save_history();

	exit(0);
}