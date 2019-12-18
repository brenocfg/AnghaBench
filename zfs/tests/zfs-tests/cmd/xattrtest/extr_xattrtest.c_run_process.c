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
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execvp (char const*,char**) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vfork () ; 
 int waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
run_process(const char *path, char *argv[])
{
	pid_t pid;
	int rc, devnull_fd;

	pid = vfork();
	if (pid == 0) {
		devnull_fd = open("/dev/null", O_WRONLY);

		if (devnull_fd < 0)
			_exit(-1);

		(void) dup2(devnull_fd, STDOUT_FILENO);
		(void) dup2(devnull_fd, STDERR_FILENO);
		close(devnull_fd);

		(void) execvp(path, argv);
		_exit(-1);
	} else if (pid > 0) {
		int status;

		while ((rc = waitpid(pid, &status, 0)) == -1 &&
		    errno == EINTR) { }

		if (rc < 0 || !WIFEXITED(status))
			return (-1);

		return (WEXITSTATUS(status));
	}

	return (-1);
}