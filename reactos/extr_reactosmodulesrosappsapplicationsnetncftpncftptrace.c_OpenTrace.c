#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pathName ;
struct TYPE_3__ {char* ourHostName; int hresult; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FOPEN_WRITE_TEXT ; 
 int /*<<< orphan*/  FTPInitializeOurHostName (TYPE_1__*) ; 
 int /*<<< orphan*/  OurDirectoryPath (char*,int,char*) ; 
 int /*<<< orphan*/  _chmod (char*,int) ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__ gLib ; 
 char* gLibNcFTPVersion ; 
 char* gOS ; 
 char* gOurDirectoryPath ; 
 int /*<<< orphan*/ * gTraceFile ; 
 int /*<<< orphan*/  gTraceTime ; 
 char* gVersion ; 
 scalar_t__ getenv (char*) ; 
 int getpid () ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void
OpenTrace(void)
{
	FILE *fp;
	char pathName[256];
	char tName[32];
	int pid;
	const char *cp;
#if defined(HAVE_SYS_UTSNAME_H) && defined(HAVE_UNAME)
	struct utsname u;
#endif

	if (gOurDirectoryPath[0] == '\0')
		return;		/* Don't create in root directory. */

	(void) sprintf(tName, "trace.%u", (unsigned int) (pid = getpid()));
	(void) OurDirectoryPath(pathName, sizeof(pathName), tName);

	fp = fopen(pathName, FOPEN_WRITE_TEXT);
	if (fp != NULL) {
		(void) _chmod(pathName, 00600);
#ifdef HAVE_SETVBUF
		(void) setvbuf(fp, gTraceLBuf, _IOLBF, sizeof(gTraceLBuf));
#endif	/* HAVE_SETVBUF */
		/* Opened the trace file. */
		(void) time(&gTraceTime);
		(void) fprintf(fp, "SESSION STARTED at:  %s", ctime(&gTraceTime));
		(void) fprintf(fp, "   Program Version:  %s\n", gVersion + 5);
		(void) fprintf(fp, "   Library Version:  %s\n", gLibNcFTPVersion + 5);
		(void) fprintf(fp, "        Process ID:  %u\n", pid);
		if (gOS[0] != '\0')
			(void) fprintf(fp, "          Platform:  %s\n", gOS);
#if defined(HAVE_SYS_UTSNAME_H) && defined(HAVE_UNAME)
		if (uname(&u) == 0) {
			(void) fprintf(fp, "             Uname:  %.63s|%.63s|%.63s|%.63s|%.63s\r\n", u.sysname, u.nodename, u.release, u.version, u.machine);
		}
#endif	/* UNAME */
		FTPInitializeOurHostName(&gLib);
		(void) fprintf(fp, "          Hostname:  %s  (rc=%d)\n", gLib.ourHostName, gLib.hresult);
		cp = (const char *) getenv("TERM");
		if (cp == NULL)
			cp = "unknown?";
		(void) fprintf(fp, "          Terminal:  %s\n", cp);
		gTraceFile = fp;
	}
}