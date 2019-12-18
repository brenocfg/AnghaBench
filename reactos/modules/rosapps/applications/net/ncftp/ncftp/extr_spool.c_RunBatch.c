#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int pid_t ;
typedef  int /*<<< orphan*/  ncftpbatch ;
struct TYPE_4__ {scalar_t__ lip; } ;
typedef  int /*<<< orphan*/  FTPLibraryInfo ;
typedef  int /*<<< orphan*/  FTPConnectionInfo ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  BINDIR ; 
 int /*<<< orphan*/  CloseControlConnection (TYPE_1__* const) ; 
#define  ERROR_BAD_FORMAT 130 
#define  ERROR_FILE_NOT_FOUND 129 
#define  ERROR_PATH_NOT_FOUND 128 
 int /*<<< orphan*/  OurInstallationPath (char*,int,char*) ; 
 int /*<<< orphan*/  PWrite (int,char const*,int) ; 
 int /*<<< orphan*/  STRNCAT (char*,char*) ; 
 int /*<<< orphan*/  STRNCPY (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_SHOWNORMAL ; 
 int WinExec (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  execv (char*,char**) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 char* gOurInstallationPath ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
RunBatch(int Xstruct, const FTPCIPtr cip)
{
#if defined(WIN32) || defined(_WINDOWS)
	char ncftpbatch[260];
	const char *prog;
	int winExecResult;

	if (gOurInstallationPath[0] == '\0') {
		(void) fprintf(stderr, "Cannot find path to %s.  Please re-run Setup.\n", "ncftpbatch.exe");
		return;
	}
	prog = ncftpbatch;
	OurInstallationPath(ncftpbatch, sizeof(ncftpbatch), "ncftpbatch.exe");

	winExecResult = WinExec(prog, SW_SHOWNORMAL);
	if (winExecResult <= 31) switch (winExecResult) {
		case ERROR_BAD_FORMAT:
			fprintf(stderr, "Could not run %s: %s\n", prog, "The .EXE file is invalid");
			return;
		case ERROR_FILE_NOT_FOUND:
			fprintf(stderr, "Could not run %s: %s\n", prog, "The specified file was not found.");
			return;
		case ERROR_PATH_NOT_FOUND:
			fprintf(stderr, "Could not run %s: %s\n", prog, "The specified path was not found.");
			return;
		default:
			fprintf(stderr, "Could not run %s: Unknown error #%d.\n", prog, winExecResult);
			return;
	}
#else
	int pfd[2];
	char pfdstr[32];
	char *argv[8];
	pid_t pid = 0;
#ifdef BINDIR
	char ncftpbatch[256];

	STRNCPY(ncftpbatch, BINDIR);
	STRNCAT(ncftpbatch, "/");
	STRNCAT(ncftpbatch, "ncftpbatch");
#endif	/* BINDIR */

	if (Xstruct != 0) {
		if (pipe(pfd) < 0) {
			perror("pipe");
		}

		(void) sprintf(pfdstr, "%d", pfd[0]);
		pid = fork();
		if (pid < 0) {
			(void) close(pfd[0]);
			(void) close(pfd[1]);
			perror("fork");
		} else if (pid == 0) {
			(void) close(pfd[1]);	/* Child closes write end. */
			argv[0] = (char *) "ncftpbatch";
#ifdef DEBUG_NCFTPBATCH
			argv[1] = (char *) "-SD";
#else
			argv[1] = (char *) "-d";
#endif
			argv[2] = (char *) "-|";
			argv[3] = pfdstr;
			argv[4] = NULL;

#ifdef BINDIR
			(void) execv(ncftpbatch, argv);
			(void) fprintf(stderr, "Could not run %s.  Is it in installed as %s?\n", argv[0], ncftpbatch);
#else	/* BINDIR */
			(void) execvp(argv[0], argv);
			(void) fprintf(stderr, "Could not run %s.  Is it in your $PATH?\n", argv[0]);
#endif	/* BINDIR */
			perror(argv[0]);
			exit(1);
		}
		(void) close(pfd[0]);	/* Parent closes read end. */
		(void) PWrite(pfd[1], (const char *) cip->lip, sizeof(FTPLibraryInfo));
		(void) PWrite(pfd[1], (const char *) cip, sizeof(FTPConnectionInfo));
		(void) close(pfd[1]);	/* Parent closes read end. */

		/* Close it now, or else this process would send
		 * the server a QUIT message.  This will cause it
		 * to think it already has.
		 */
		CloseControlConnection(cip);
	} else {
		pid = fork();
		if (pid < 0) {
			perror("fork");
		} else if (pid == 0) {
			argv[0] = (char *) "ncftpbatch";
			argv[1] = (char *) "-d";
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
		}
	}

	if (pid > 1) {
#ifdef HAVE_WAITPID
		(void) waitpid(pid, NULL, 0);
#else
		(void) wait(NULL);
#endif
	}
#endif
}