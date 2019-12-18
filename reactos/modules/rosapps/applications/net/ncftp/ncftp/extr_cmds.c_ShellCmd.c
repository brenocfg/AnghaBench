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
typedef  int /*<<< orphan*/  vsigproc_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  FTPSigProc ;
typedef  int /*<<< orphan*/  CommandPtr ;
typedef  int /*<<< orphan*/  ArgvInfoPtr ;

/* Variables and functions */
 int /*<<< orphan*/  ARGSUSED (int /*<<< orphan*/ ) ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  NcSignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGINT ; 
 scalar_t__ SIG_IGN ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execl (char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  execvp (char const*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 char* gShell ; 
 int /*<<< orphan*/  gUnusedArg ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ wait (int*) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

void
ShellCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
#if defined(WIN32) || defined(_WINDOWS)
#else
	const char *cp;
	pid_t pid;
	int status;
	vsigproc_t osigint;

	osigint = NcSignal(SIGINT, (FTPSigProc) SIG_IGN);
	ARGSUSED(gUnusedArg);
	pid = fork();
	if (pid < (pid_t) 0) {
		perror("fork");
	} else if (pid == 0) {
		cp = strrchr(gShell, '/');
		if (cp == NULL)
			cp = gShell;	/* bug */
		else
			cp++;
		if (argc == 1) {
			execl(gShell, cp, NULL);
			perror(gShell);
			exit(1);
		} else {
			execvp(argv[1], (char **) argv + 1);
			perror(gShell);
			exit(1);
		}
	} else {
		/* parent */
		for (;;) {
#ifdef HAVE_WAITPID
			if ((waitpid(pid, &status, 0) < 0) && (errno != EINTR))
				break;
#else
			if ((wait(&status) < 0) && (errno != EINTR))
				break;
#endif
			if (WIFEXITED(status) || WIFSIGNALED(status))
				break;		/* done */
		}
	}
	(void) NcSignal(SIGINT, osigint);
#endif
}