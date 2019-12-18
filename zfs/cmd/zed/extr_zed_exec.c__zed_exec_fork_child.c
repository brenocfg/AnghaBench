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
typedef  int /*<<< orphan*/  uint64_t ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ ENAMETOOLONG ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  SIGKILL ; 
 scalar_t__ STDERR_FILENO ; 
 scalar_t__ STDIN_FILENO ; 
 scalar_t__ STDOUT_FILENO ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WNOHANG ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 scalar_t__ ZEVENT_FILENO ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dup2 (int,scalar_t__) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execle (char*,char const*,int /*<<< orphan*/ *,char**) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nanosleep (struct timespec*,int /*<<< orphan*/ *) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  strsignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umask (int) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zed_file_close_from (scalar_t__) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,char const*,scalar_t__,...) ; 

__attribute__((used)) static void
_zed_exec_fork_child(uint64_t eid, const char *dir, const char *prog,
    char *env[], int zfd)
{
	char path[PATH_MAX];
	int n;
	pid_t pid;
	int fd;
	pid_t wpid;
	int status;

	assert(dir != NULL);
	assert(prog != NULL);
	assert(env != NULL);
	assert(zfd >= 0);

	n = snprintf(path, sizeof (path), "%s/%s", dir, prog);
	if ((n < 0) || (n >= sizeof (path))) {
		zed_log_msg(LOG_WARNING,
		    "Failed to fork \"%s\" for eid=%llu: %s",
		    prog, eid, strerror(ENAMETOOLONG));
		return;
	}
	pid = fork();
	if (pid < 0) {
		zed_log_msg(LOG_WARNING,
		    "Failed to fork \"%s\" for eid=%llu: %s",
		    prog, eid, strerror(errno));
		return;
	} else if (pid == 0) {
		(void) umask(022);
		if ((fd = open("/dev/null", O_RDWR)) != -1) {
			(void) dup2(fd, STDIN_FILENO);
			(void) dup2(fd, STDOUT_FILENO);
			(void) dup2(fd, STDERR_FILENO);
		}
		(void) dup2(zfd, ZEVENT_FILENO);
		zed_file_close_from(ZEVENT_FILENO + 1);
		execle(path, prog, NULL, env);
		_exit(127);
	}

	/* parent process */

	zed_log_msg(LOG_INFO, "Invoking \"%s\" eid=%llu pid=%d",
	    prog, eid, pid);

	/* FIXME: Timeout rogue child processes with sigalarm? */

	/*
	 * Wait for child process using WNOHANG to limit
	 * the time spent waiting to 10 seconds (10,000ms).
	 */
	for (n = 0; n < 1000; n++) {
		wpid = waitpid(pid, &status, WNOHANG);
		if (wpid == (pid_t)-1) {
			if (errno == EINTR)
				continue;
			zed_log_msg(LOG_WARNING,
			    "Failed to wait for \"%s\" eid=%llu pid=%d",
			    prog, eid, pid);
			break;
		} else if (wpid == 0) {
			struct timespec t;

			/* child still running */
			t.tv_sec = 0;
			t.tv_nsec = 10000000;	/* 10ms */
			(void) nanosleep(&t, NULL);
			continue;
		}

		if (WIFEXITED(status)) {
			zed_log_msg(LOG_INFO,
			    "Finished \"%s\" eid=%llu pid=%d exit=%d",
			    prog, eid, pid, WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
			zed_log_msg(LOG_INFO,
			    "Finished \"%s\" eid=%llu pid=%d sig=%d/%s",
			    prog, eid, pid, WTERMSIG(status),
			    strsignal(WTERMSIG(status)));
		} else {
			zed_log_msg(LOG_INFO,
			    "Finished \"%s\" eid=%llu pid=%d status=0x%X",
			    prog, eid, (unsigned int) status);
		}
		break;
	}

	/*
	 * kill child process after 10 seconds
	 */
	if (wpid == 0) {
		zed_log_msg(LOG_WARNING, "Killing hung \"%s\" pid=%d",
		    prog, pid);
		(void) kill(pid, SIGKILL);
	}
}