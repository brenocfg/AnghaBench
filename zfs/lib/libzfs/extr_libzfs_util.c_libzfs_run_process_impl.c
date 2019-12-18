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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int EPIPE ; 
 int NO_DEFAULT_PATH ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int STDERR_VERBOSE ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int STDOUT_VERBOSE ; 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execv (char const*,char**) ; 
 int /*<<< orphan*/  execve (char const*,char**,char**) ; 
 int /*<<< orphan*/  execvp (char const*,char**) ; 
 int /*<<< orphan*/  execvpe (char const*,char**,char**) ; 
 int libzfs_read_stdout_from_fd (int,char***) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int pipe (int*) ; 
 scalar_t__ vfork () ; 
 int waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
libzfs_run_process_impl(const char *path, char *argv[], char *env[], int flags,
    char **lines[], int *lines_cnt)
{
	pid_t pid;
	int error, devnull_fd;
	int link[2];

	/*
	 * Setup a pipe between our child and parent process if we're
	 * reading stdout.
	 */
	if ((lines != NULL) && pipe(link) == -1)
		return (-EPIPE);

	pid = vfork();
	if (pid == 0) {
		/* Child process */
		devnull_fd = open("/dev/null", O_WRONLY);

		if (devnull_fd < 0)
			_exit(-1);

		if (!(flags & STDOUT_VERBOSE) && (lines == NULL))
			(void) dup2(devnull_fd, STDOUT_FILENO);
		else if (lines != NULL) {
			/* Save the output to lines[] */
			dup2(link[1], STDOUT_FILENO);
			close(link[0]);
			close(link[1]);
		}

		if (!(flags & STDERR_VERBOSE))
			(void) dup2(devnull_fd, STDERR_FILENO);

		close(devnull_fd);

		if (flags & NO_DEFAULT_PATH) {
			if (env == NULL)
				execv(path, argv);
			else
				execve(path, argv, env);
		} else {
			if (env == NULL)
				execvp(path, argv);
			else
				execvpe(path, argv, env);
		}

		_exit(-1);
	} else if (pid > 0) {
		/* Parent process */
		int status;

		while ((error = waitpid(pid, &status, 0)) == -1 &&
		    errno == EINTR) { }
		if (error < 0 || !WIFEXITED(status))
			return (-1);

		if (lines != NULL) {
			close(link[1]);
			*lines_cnt = libzfs_read_stdout_from_fd(link[0], lines);
		}
		return (WEXITSTATUS(status));
	}

	return (-1);
}