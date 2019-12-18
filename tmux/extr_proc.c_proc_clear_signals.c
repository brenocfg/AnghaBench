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
struct tmuxproc {int /*<<< orphan*/  ev_sigwinch; int /*<<< orphan*/  ev_sigusr2; int /*<<< orphan*/  ev_sigusr1; int /*<<< orphan*/  ev_sigterm; int /*<<< orphan*/  ev_sigcont; int /*<<< orphan*/  ev_sigchld; int /*<<< orphan*/  ev_sighup; } ;
struct sigaction {int /*<<< orphan*/  sa_handler; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_RESTART ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  SIGWINCH ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_del (int /*<<< orphan*/ *) ; 

void
proc_clear_signals(struct tmuxproc *tp, int defaults)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof sa);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_DFL;

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGPIPE, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);

	signal_del(&tp->ev_sighup);
	signal_del(&tp->ev_sigchld);
	signal_del(&tp->ev_sigcont);
	signal_del(&tp->ev_sigterm);
	signal_del(&tp->ev_sigusr1);
	signal_del(&tp->ev_sigusr2);
	signal_del(&tp->ev_sigwinch);

	if (defaults) {
		sigaction(SIGHUP, &sa, NULL);
		sigaction(SIGCHLD, &sa, NULL);
		sigaction(SIGCONT, &sa, NULL);
		sigaction(SIGTERM, &sa, NULL);
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		sigaction(SIGWINCH, &sa, NULL);
	}
}