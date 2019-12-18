#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sigaction {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_4__ {struct sigaction* sigttou_action_ptr; struct sigaction* sigttin_action_ptr; int /*<<< orphan*/ * sigmask_ptr; } ;
typedef  TYPE_1__ signal_configuration_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_FATAL (char*) ; 
 int /*<<< orphan*/  PRINT_TRACE (char*) ; 
 int /*<<< orphan*/  PR_SET_PDEATHSIG ; 
 scalar_t__ configure_signals (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  free (char***) ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parent_death_signal ; 
 int parse_args (int,char**,char****,int*) ; 
 scalar_t__ parse_env () ; 
 scalar_t__ prctl (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ reap_zombies (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  reaper_check () ; 
 scalar_t__ register_subreaper () ; 
 int spawn (TYPE_1__*,char**,int /*<<< orphan*/ *) ; 
 scalar_t__ wait_and_forward_signal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
	pid_t child_pid;

	// Those are passed to functions to get an exitcode back.
	int child_exitcode = -1;  // This isn't a valid exitcode, and lets us tell whether the child has exited.
	int parse_exitcode = 1;   // By default, we exit with 1 if parsing fails.

	/* Parse command line arguments */
	char* (*child_args_ptr)[];
	int parse_args_ret = parse_args(argc, argv, &child_args_ptr, &parse_exitcode);
	if (parse_args_ret) {
		return parse_exitcode;
	}

	/* Parse environment */
	if (parse_env()) {
		return 1;
	}

	/* Configure signals */
	sigset_t parent_sigset, child_sigset;
	struct sigaction sigttin_action, sigttou_action;
	memset(&sigttin_action, 0, sizeof sigttin_action);
	memset(&sigttou_action, 0, sizeof sigttou_action);

	signal_configuration_t child_sigconf = {
		.sigmask_ptr = &child_sigset,
		.sigttin_action_ptr = &sigttin_action,
		.sigttou_action_ptr = &sigttou_action,
	};

	if (configure_signals(&parent_sigset, &child_sigconf)) {
		return 1;
	}

	/* Trigger signal on this process when the parent process exits. */
	if (parent_death_signal && prctl(PR_SET_PDEATHSIG, parent_death_signal)) {
		PRINT_FATAL("Failed to set up parent death signal");
		return 1;
	 }

#if HAS_SUBREAPER
	/* If available and requested, register as a subreaper */
	if (register_subreaper()) {
		return 1;
	};
#endif

	/* Are we going to reap zombies properly? If not, warn. */
	reaper_check();

	/* Go on */
	int spawn_ret = spawn(&child_sigconf, *child_args_ptr, &child_pid);
	if (spawn_ret) {
		return spawn_ret;
	}
	free(child_args_ptr);

	while (1) {
		/* Wait for one signal, and forward it */
		if (wait_and_forward_signal(&parent_sigset, child_pid)) {
			return 1;
		}

		/* Now, reap zombies */
		if (reap_zombies(child_pid, &child_exitcode)) {
			return 1;
		}

		if (child_exitcode != -1) {
			PRINT_TRACE("Exiting: child has exited");
			return child_exitcode;
		}
	}
}