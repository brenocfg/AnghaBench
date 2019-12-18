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
 int /*<<< orphan*/  BINDIR ; 
 int /*<<< orphan*/  STRNCAT (char*,char*) ; 
 int /*<<< orphan*/  STRNCPY (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execv (char*,char**) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitpid (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
Jobs(void)
{
#if defined(WIN32) || defined(_WINDOWS)
	assert(0); // Not supported
#else
	char *argv[8];
	pid_t pid;
#ifdef BINDIR
	char ncftpbatch[256];

	STRNCPY(ncftpbatch, BINDIR);
	STRNCAT(ncftpbatch, "/");
	STRNCAT(ncftpbatch, "ncftpbatch");
#endif	/* BINDIR */

	pid = fork();
	if (pid < 0) {
		perror("fork");
	} else if (pid == 0) {
		argv[0] = (char *) "ncftpbatch";
		argv[1] = (char *) "-l";
		argv[2] = NULL;

#ifdef BINDIR
		(void) execv(ncftpbatch, argv);
		(void) fprintf(stderr, "Could not run %s.  Is it in installed as %s?\n", argv[0], ncftpbatch);
#else	/* BINDIR */
		(void) execvp(argv[0], argv);
		(void) fprintf(stderr, "Could not run %s.  Is it in your $PATH?\n", argv[0]);
#endif	/* BINDIR */
		perror(argv[0]);
		exit(1);
	} else {
#ifdef HAVE_WAITPID
		(void) waitpid(pid, NULL, 0);
#else
		(void) wait(NULL);
#endif
	}
#endif
}