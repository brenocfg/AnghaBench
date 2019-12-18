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
struct sigaction {scalar_t__ sa_flags; void* sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  void* sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  perror (char*) ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigdisable ; 
 int /*<<< orphan*/  sigemptyset (void**) ; 
 int /*<<< orphan*/  sigexit ; 

int
signals_install_handlers(void)
{
#if defined(HAVE_SIGNAL_H) && !defined(__WIN32__)
	struct sigaction sigact;
	sigset_t sigset;
	int r;
	sigemptyset(&sigset);

	/* Install signal handler for INT and TERM signals */
	sigact.sa_handler = sigexit;
	sigact.sa_mask = sigset;
	sigact.sa_flags = 0;

	r = sigaction(SIGINT, &sigact, NULL);
	if (r < 0) {
		perror("sigaction");
		return -1;
	}

	r = sigaction(SIGTERM, &sigact, NULL);
	if (r < 0) {
		perror("sigaction");
		return -1;
	}

	/* Install signal handler for USR1 signal */
	sigact.sa_handler = sigdisable;
	sigact.sa_mask = sigset;
	sigact.sa_flags = 0;

	r = sigaction(SIGUSR1, &sigact, NULL);
	if (r < 0) {
		perror("sigaction");
		return -1;
	}

	/* Ignore CHLD signal. This causes child processes
	   (hooks) to be reaped automatically. */
	sigact.sa_handler = SIG_IGN;
	sigact.sa_mask = sigset;
	sigact.sa_flags = 0;

	r = sigaction(SIGCHLD, &sigact, NULL);
	if (r < 0) {
		perror("sigaction");
		return -1;
	}
#endif /* HAVE_SIGNAL_H && ! __WIN32__ */

	return 0;
}