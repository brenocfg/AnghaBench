#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct cmd_results {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {scalar_t__ validating; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DEFER ; 
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  SWAY_INFO ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  close (int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* config ; 
 int /*<<< orphan*/  execl (char*,char*,char*,char*,void*) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* join_args (char**,int) ; 
 scalar_t__ pipe (int*) ; 
 int read (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  root_record_workspace_pid (scalar_t__) ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strip_quotes (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  waitpid (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int write (int,int /*<<< orphan*/ *,int) ; 

struct cmd_results *cmd_exec_always(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if (!config->active || config->validating) {
		return cmd_results_new(CMD_DEFER, NULL);
	}
	if ((error = checkarg(argc, argv[-1], EXPECTED_AT_LEAST, 1))) {
		return error;
	}

	char *tmp = NULL;
	if (strcmp(argv[0], "--no-startup-id") == 0) {
		sway_log(SWAY_INFO, "exec switch '--no-startup-id' not supported, ignored.");
		--argc; ++argv;
		if ((error = checkarg(argc, argv[-1], EXPECTED_AT_LEAST, 1))) {
			return error;
		}
	}

	if (argc == 1 && (argv[0][0] == '\'' || argv[0][0] == '"')) {
		tmp = strdup(argv[0]);
		strip_quotes(tmp);
	} else {
		tmp = join_args(argv, argc);
	}

	// Put argument into cmd array
	char cmd[4096];
	strncpy(cmd, tmp, sizeof(cmd) - 1);
	cmd[sizeof(cmd) - 1] = 0;
	free(tmp);
	sway_log(SWAY_DEBUG, "Executing %s", cmd);

	int fd[2];
	if (pipe(fd) != 0) {
		sway_log(SWAY_ERROR, "Unable to create pipe for fork");
	}

	pid_t pid, child;
	// Fork process
	if ((pid = fork()) == 0) {
		// Fork child process again
		setsid();
		sigset_t set;
		sigemptyset(&set);
		sigprocmask(SIG_SETMASK, &set, NULL);
		close(fd[0]);
		if ((child = fork()) == 0) {
			close(fd[1]);
			execl("/bin/sh", "/bin/sh", "-c", cmd, (void *)NULL);
			_exit(0);
		}
		ssize_t s = 0;
		while ((size_t)s < sizeof(pid_t)) {
			s += write(fd[1], ((uint8_t *)&child) + s, sizeof(pid_t) - s);
		}
		close(fd[1]);
		_exit(0); // Close child process
	} else if (pid < 0) {
		close(fd[0]);
		close(fd[1]);
		return cmd_results_new(CMD_FAILURE, "fork() failed");
	}
	close(fd[1]); // close write
	ssize_t s = 0;
	while ((size_t)s < sizeof(pid_t)) {
		s += read(fd[0], ((uint8_t *)&child) + s, sizeof(pid_t) - s);
	}
	close(fd[0]);
	// cleanup child process
	waitpid(pid, NULL, 0);
	if (child > 0) {
		sway_log(SWAY_DEBUG, "Child process created with pid %d", child);
		root_record_workspace_pid(child);
	} else {
		return cmd_results_new(CMD_FAILURE, "Second fork() failed");
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}