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
struct tmuxproc {void (* signalcb ) (int) ;int /*<<< orphan*/  ev_sigwinch; int /*<<< orphan*/  ev_sigusr2; int /*<<< orphan*/  ev_sigusr1; int /*<<< orphan*/  ev_sigterm; int /*<<< orphan*/  ev_sigcont; int /*<<< orphan*/  ev_sigchld; int /*<<< orphan*/  ev_sighup; } ;
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
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_signal_cb ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tmuxproc*) ; 

void
proc_set_signals(struct tmuxproc *tp, void (*signalcb)(int))
{
	struct sigaction	sa;

	tp->signalcb = signalcb;

	memset(&sa, 0, sizeof sa);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGPIPE, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);

	signal_set(&tp->ev_sighup, SIGHUP, proc_signal_cb, tp);
	signal_add(&tp->ev_sighup, NULL);
	signal_set(&tp->ev_sigchld, SIGCHLD, proc_signal_cb, tp);
	signal_add(&tp->ev_sigchld, NULL);
	signal_set(&tp->ev_sigcont, SIGCONT, proc_signal_cb, tp);
	signal_add(&tp->ev_sigcont, NULL);
	signal_set(&tp->ev_sigterm, SIGTERM, proc_signal_cb, tp);
	signal_add(&tp->ev_sigterm, NULL);
	signal_set(&tp->ev_sigusr1, SIGUSR1, proc_signal_cb, tp);
	signal_add(&tp->ev_sigusr1, NULL);
	signal_set(&tp->ev_sigusr2, SIGUSR2, proc_signal_cb, tp);
	signal_add(&tp->ev_sigusr2, NULL);
	signal_set(&tp->ev_sigwinch, SIGWINCH, proc_signal_cb, tp);
	signal_add(&tp->ev_sigwinch, NULL);
}