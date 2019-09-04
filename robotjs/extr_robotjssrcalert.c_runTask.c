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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int EXEC_FAILED ; 
 int FORK_FAILED ; 
 int TASK_SUCCESS ; 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  execvp (char const*,char* const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  wait (int*) ; 

__attribute__((used)) static int runTask(const char *taskname, char * const argv[], int *exit_status)
{
	pid_t pid;
	int status;

	switch (pid = fork()) {
		case -1: /* Failed to fork */
			perror("fork");
			return FORK_FAILED; /* Failed to fork. */
		case 0: /* Child process */
			execvp(taskname, argv);
			exit(42); /* Failed to run task. */
		default: /* Parent process */
			wait(&status); /* Block execution until finished. */

			if (!WIFEXITED(status) || (status = WEXITSTATUS(status)) == 42) {
				return EXEC_FAILED; /* Task failed to run. */
			}
			if (exit_status != NULL) *exit_status = status;
			return TASK_SUCCESS; /* Success! */
	}
}