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
struct sigaction {int /*<<< orphan*/  sa_handler; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_EXIT_LOST_TTY ; 
 int /*<<< orphan*/  CLIENT_EXIT_TERMINATED ; 
 int /*<<< orphan*/  MSG_EXITING ; 
 int /*<<< orphan*/  MSG_RESIZE ; 
 int /*<<< orphan*/  MSG_WAKEUP ; 
 int /*<<< orphan*/  SA_RESTART ; 
 int SIGCHLD ; 
#define  SIGCONT 131 
#define  SIGHUP 130 
#define  SIGTERM 129 
 int /*<<< orphan*/  SIGTSTP ; 
#define  SIGWINCH 128 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  WAIT_ANY ; 
 int /*<<< orphan*/  WNOHANG ; 
 int /*<<< orphan*/  client_attached ; 
 int /*<<< orphan*/  client_exitreason ; 
 int client_exitval ; 
 int /*<<< orphan*/  client_peer ; 
 int /*<<< orphan*/  client_proc ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
client_signal(int sig)
{
	struct sigaction sigact;
	int		 status;

	if (sig == SIGCHLD)
		waitpid(WAIT_ANY, &status, WNOHANG);
	else if (!client_attached) {
		if (sig == SIGTERM)
			proc_exit(client_proc);
	} else {
		switch (sig) {
		case SIGHUP:
			client_exitreason = CLIENT_EXIT_LOST_TTY;
			client_exitval = 1;
			proc_send(client_peer, MSG_EXITING, -1, NULL, 0);
			break;
		case SIGTERM:
			client_exitreason = CLIENT_EXIT_TERMINATED;
			client_exitval = 1;
			proc_send(client_peer, MSG_EXITING, -1, NULL, 0);
			break;
		case SIGWINCH:
			proc_send(client_peer, MSG_RESIZE, -1, NULL, 0);
			break;
		case SIGCONT:
			memset(&sigact, 0, sizeof sigact);
			sigemptyset(&sigact.sa_mask);
			sigact.sa_flags = SA_RESTART;
			sigact.sa_handler = SIG_IGN;
			if (sigaction(SIGTSTP, &sigact, NULL) != 0)
				fatal("sigaction failed");
			proc_send(client_peer, MSG_WAKEUP, -1, NULL, 0);
			break;
		}
	}
}