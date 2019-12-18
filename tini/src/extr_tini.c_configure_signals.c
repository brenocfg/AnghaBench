#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_3__ {int /*<<< orphan*/  sigttou_action_ptr; int /*<<< orphan*/  sigttin_action_ptr; int /*<<< orphan*/  sigmask_ptr; } ;
typedef  TYPE_1__ signal_configuration_t ;

/* Variables and functions */
 size_t ARRAY_LEN (int*) ; 
 int /*<<< orphan*/  PRINT_FATAL (char*,...) ; 
 int SIGABRT ; 
 int SIGBUS ; 
 int SIGFPE ; 
 int SIGILL ; 
 int SIGSEGV ; 
 int SIGSYS ; 
 int SIGTRAP ; 
 int SIGTTIN ; 
 int SIGTTOU ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sigaction (int,struct sigaction*,int /*<<< orphan*/ ) ; 
 scalar_t__ sigdelset (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ sigfillset (int /*<<< orphan*/ * const) ; 
 scalar_t__ sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int configure_signals(sigset_t* const parent_sigset_ptr, const signal_configuration_t* const sigconf_ptr) {
	/* Block all signals that are meant to be collected by the main loop */
	if (sigfillset(parent_sigset_ptr)) {
		PRINT_FATAL("sigfillset failed: '%s'", strerror(errno));
		return 1;
	}

	// These ones shouldn't be collected by the main loop
	uint i;
	int signals_for_tini[] = {SIGFPE, SIGILL, SIGSEGV, SIGBUS, SIGABRT, SIGTRAP, SIGSYS, SIGTTIN, SIGTTOU};
	for (i = 0; i < ARRAY_LEN(signals_for_tini); i++) {
		if (sigdelset(parent_sigset_ptr, signals_for_tini[i])) {
			PRINT_FATAL("sigdelset failed: '%i'", signals_for_tini[i]);
			return 1;
		}
	}

	if (sigprocmask(SIG_SETMASK, parent_sigset_ptr, sigconf_ptr->sigmask_ptr)) {
		PRINT_FATAL("sigprocmask failed: '%s'", strerror(errno));
		return 1;
	}

	// Handle SIGTTIN and SIGTTOU separately. Since Tini makes the child process group
	// the foreground process group, there's a chance Tini can end up not controlling the tty.
	// If TOSTOP is set on the tty, this could block Tini on writing debug messages. We don't
	// want that. Ignore those signals.
	struct sigaction ign_action;
	memset(&ign_action, 0, sizeof ign_action);

	ign_action.sa_handler = SIG_IGN;
	sigemptyset(&ign_action.sa_mask);

	if (sigaction(SIGTTIN, &ign_action, sigconf_ptr->sigttin_action_ptr)) {
		PRINT_FATAL("Failed to ignore SIGTTIN");
		return 1;
	}

	if (sigaction(SIGTTOU, &ign_action, sigconf_ptr->sigttou_action_ptr)) {
		PRINT_FATAL("Failed to ignore SIGTTOU");
		return 1;
	}

	return 0;
}