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
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int SA_CONFIG_ERR ; 
 int SA_OK ; 
 int SA_SYSTEM_ERR ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ dup2 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int execlp (char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int mkstemp (char*) ; 
 int nfs_exportfs_temp_fd ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_check_exportfs(void)
{
	pid_t pid;
	int rc, status;
	static char nfs_exportfs_tempfile[] = "/tmp/exportfs.XXXXXX";

	/*
	 * Close any existing temporary copies of output from exportfs.
	 * We have already called unlink() so file will be deleted.
	 */
	if (nfs_exportfs_temp_fd >= 0)
		close(nfs_exportfs_temp_fd);

	nfs_exportfs_temp_fd = mkstemp(nfs_exportfs_tempfile);

	if (nfs_exportfs_temp_fd < 0)
		return (SA_SYSTEM_ERR);

	unlink(nfs_exportfs_tempfile);

	(void) fcntl(nfs_exportfs_temp_fd, F_SETFD, FD_CLOEXEC);

	pid = fork();

	if (pid < 0) {
		(void) close(nfs_exportfs_temp_fd);
		nfs_exportfs_temp_fd = -1;
		return (SA_SYSTEM_ERR);
	}

	if (pid > 0) {
		while ((rc = waitpid(pid, &status, 0)) <= 0 &&
		    errno == EINTR) { }

		if (rc <= 0) {
			(void) close(nfs_exportfs_temp_fd);
			nfs_exportfs_temp_fd = -1;
			return (SA_SYSTEM_ERR);
		}

		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
			(void) close(nfs_exportfs_temp_fd);
			nfs_exportfs_temp_fd = -1;
			return (SA_CONFIG_ERR);
		}

		return (SA_OK);
	}

	/* child */

	/* exportfs -v */

	if (dup2(nfs_exportfs_temp_fd, STDOUT_FILENO) < 0)
		exit(1);

	rc = execlp("/usr/sbin/exportfs", "exportfs", "-v", NULL);

	if (rc < 0) {
		exit(1);
	}

	exit(0);
}