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

/* Variables and functions */
 int /*<<< orphan*/  CheckForNewV3User () ; 
 int FTPInitLibrary (int /*<<< orphan*/ *) ; 
 char* FTPStrError (int) ; 
 int /*<<< orphan*/  GetScreenColumns () ; 
 int /*<<< orphan*/  GetoptReset () ; 
 int /*<<< orphan*/  InitCommandList () ; 
 int /*<<< orphan*/  InitConnectionInfo () ; 
 int /*<<< orphan*/  InitLineList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitLog () ; 
 int /*<<< orphan*/  InitLs () ; 
 int /*<<< orphan*/  InitPrefs () ; 
 int /*<<< orphan*/  InitUserInfo () ; 
 int /*<<< orphan*/  LoadFirewallPrefs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadPrefs () ; 
 int /*<<< orphan*/  TruncBatchLog () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int gIsTTY ; 
 int gIsTTYr ; 
 int /*<<< orphan*/  gLib ; 
 int /*<<< orphan*/  gStartupURLCdList ; 
 scalar_t__ getpid () ; 
 int getppid () ; 
 scalar_t__ isatty (int) ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
PreInit(void)
{
	int result;

#if defined(WIN32) || defined(_WINDOWS)
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		fprintf(stderr, "could not initialize winsock\n");
		exit(1);
	}
	wsaInit++;
#endif

#ifdef HAVE_SETLOCALE
	setlocale(LC_ALL, "");
#endif
#if defined(WIN32) || defined(_WINDOWS)
	gIsTTY = 1;
	gIsTTYr = 1;
#else
	gIsTTY = ((isatty(2) != 0) && (getppid() > 1)) ? 1 : 0;
	gIsTTYr = ((isatty(0) != 0) && (getppid() > 1)) ? 1 : 0;
#endif
#ifdef SIGPOLL
	(void) NcSignal(SIGPOLL, (FTPSigProc) SIG_IGN);
#endif
	InitUserInfo();
	result = FTPInitLibrary(&gLib);
	if (result < 0) {
		(void) fprintf(stderr, "ncftp: init library error %d (%s).\n", result, FTPStrError(result));
		exit(1);
	}
#if defined(WIN32) || defined(_WINDOWS)
	srand((unsigned int) (GetTickCount() & 0x7FFF));
#else
	srand((unsigned int) getpid());
#endif
	InitLineList(&gStartupURLCdList);
	CheckForNewV3User();
	InitLog();
	InitPrefs();
	LoadFirewallPrefs(0);
	LoadPrefs();
	InitConnectionInfo();
	InitCommandList();
	InitLs();
	TruncBatchLog();
	GetoptReset();
	GetScreenColumns();
}