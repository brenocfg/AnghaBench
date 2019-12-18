#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char* string ;
typedef  int /*<<< orphan*/  longstring ;
typedef  int /*<<< orphan*/  gfile ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_5__ {int errNo; } ;
typedef  int /*<<< orphan*/  LineListPtr ;
typedef  int /*<<< orphan*/  FTPSigProc ;
typedef  TYPE_1__* FTPCIPtr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AddLine (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (TYPE_1__*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * FGets (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NcSignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintF (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGPIPE ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  kDoPerror ; 
 int kErrGlobFailed ; 
 int kNoErr ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 scalar_t__ popen (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*,char const* const) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*,char const* const) ; 

__attribute__((used)) static int
LazyUnixLocalGlob(FTPCIPtr cip, LineListPtr fileList, const char *const pattern)
{
	string cmd;
	longstring gfile;
	FILE *fp;
	FTPSigProc sp;

	/* Do it the easy way and have the shell do the dirty
	 * work for us.
	 */
#ifdef HAVE_SNPRINTF
	(void) snprintf(cmd, sizeof(cmd) - 1, "%s -c \"%s %s %s\"", "/bin/sh", "/bin/ls",
		"-d", pattern);
	cmd[sizeof(cmd) - 1] = '\0';
#else
	(void) sprintf(cmd, "%s -c \"%s %s %s\"", "/bin/sh", "/bin/ls",
		"-d", pattern);
#endif

	fp = (FILE *) popen(cmd, "r");
	if (fp == NULL) {
		Error(cip, kDoPerror, "Could not Lglob: [%s]\n", cmd);
		cip->errNo = kErrGlobFailed;
		return (kErrGlobFailed);
	}
	sp = NcSignal(SIGPIPE, (FTPSigProc) SIG_IGN);
	while (FGets(gfile, sizeof(gfile), (FILE *) fp) != NULL) {
		PrintF(cip, "  Lglob [%s]\n", gfile);
		(void) AddLine(fileList, gfile);
	}
	(void) pclose(fp);
	(void) NcSignal(SIGPIPE, sp);
	return (kNoErr);
}