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
typedef  int /*<<< orphan*/  signal_configuration_t ;
typedef  int pid_t ;

/* Variables and functions */
#define  EACCES 129 
#define  ENOENT 128 
 int /*<<< orphan*/  PRINT_FATAL (char*,char* const,...) ; 
 int /*<<< orphan*/  PRINT_INFO (char*,char* const,int) ; 
 int errno ; 
 int /*<<< orphan*/  execvp (char* const,char* const*) ; 
 int fork () ; 
 scalar_t__ isolate_child () ; 
 scalar_t__ restore_signals (int /*<<< orphan*/  const* const) ; 
 int /*<<< orphan*/  strerror (int) ; 

int spawn(const signal_configuration_t* const sigconf_ptr, char* const argv[], int* const child_pid_ptr) {
	pid_t pid;

	// TODO: check if tini was a foreground process to begin with (it's not OK to "steal" the foreground!")

	pid = fork();
	if (pid < 0) {
		PRINT_FATAL("fork failed: %s", strerror(errno));
		return 1;
	} else if (pid == 0) {

		// Put the child in a process group and make it the foreground process if there is a tty.
		if (isolate_child()) {
			return 1;
		}

		// Restore all signal handlers to the way they were before we touched them.
		if (restore_signals(sigconf_ptr)) {
			return 1;
		}

		execvp(argv[0], argv);

		// execvp will only return on an error so make sure that we check the errno
		// and exit with the correct return status for the error that we encountered
		// See: http://www.tldp.org/LDP/abs/html/exitcodes.html#EXITCODESREF
		int status = 1;
		switch (errno) {
			case ENOENT:
				status = 127;
				break;
			case EACCES:
				status = 126;
				break;
		}
		PRINT_FATAL("exec %s failed: %s", argv[0], strerror(errno));
		return status;
	} else {
		// Parent
		PRINT_INFO("Spawned child process '%s' with pid '%i'", argv[0], pid);
		*child_pid_ptr = pid;
		return 0;
	}
}