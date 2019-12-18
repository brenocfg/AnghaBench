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
struct rlimit {int member_0; int member_1; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 scalar_t__ SIGKILL ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int WTERMSIG (int) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_extended_FILE_stdio (int,int) ; 
 int /*<<< orphan*/  execv (char*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal (int,char*,...) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  getexecname () ; 
 scalar_t__ setenv (char*,char*,int) ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* umem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_free (char*,int /*<<< orphan*/ ) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_dump_core ; 
 int ztest_fd_data ; 
 int /*<<< orphan*/  ztest_fd_rand ; 

__attribute__((used)) static boolean_t
exec_child(char *cmd, char *libpath, boolean_t ignorekill, int *statusp)
{
	pid_t pid;
	int status;
	char *cmdbuf = NULL;

	pid = fork();

	if (cmd == NULL) {
		cmdbuf = umem_alloc(MAXPATHLEN, UMEM_NOFAIL);
		(void) strlcpy(cmdbuf, getexecname(), MAXPATHLEN);
		cmd = cmdbuf;
	}

	if (pid == -1)
		fatal(1, "fork failed");

	if (pid == 0) {	/* child */
		char *emptyargv[2] = { cmd, NULL };
		char fd_data_str[12];

		struct rlimit rl = { 1024, 1024 };
		(void) setrlimit(RLIMIT_NOFILE, &rl);

		(void) close(ztest_fd_rand);
		VERIFY(11 >= snprintf(fd_data_str, 12, "%d", ztest_fd_data));
		VERIFY(0 == setenv("ZTEST_FD_DATA", fd_data_str, 1));

		(void) enable_extended_FILE_stdio(-1, -1);
		if (libpath != NULL)
			VERIFY(0 == setenv("LD_LIBRARY_PATH", libpath, 1));
		(void) execv(cmd, emptyargv);
		ztest_dump_core = B_FALSE;
		fatal(B_TRUE, "exec failed: %s", cmd);
	}

	if (cmdbuf != NULL) {
		umem_free(cmdbuf, MAXPATHLEN);
		cmd = NULL;
	}

	while (waitpid(pid, &status, 0) != pid)
		continue;
	if (statusp != NULL)
		*statusp = status;

	if (WIFEXITED(status)) {
		if (WEXITSTATUS(status) != 0) {
			(void) fprintf(stderr, "child exited with code %d\n",
			    WEXITSTATUS(status));
			exit(2);
		}
		return (B_FALSE);
	} else if (WIFSIGNALED(status)) {
		if (!ignorekill || WTERMSIG(status) != SIGKILL) {
			(void) fprintf(stderr, "child died with signal %d\n",
			    WTERMSIG(status));
			exit(3);
		}
		return (B_TRUE);
	} else {
		(void) fprintf(stderr, "something strange happened to child\n");
		exit(4);
		/* NOTREACHED */
	}
}