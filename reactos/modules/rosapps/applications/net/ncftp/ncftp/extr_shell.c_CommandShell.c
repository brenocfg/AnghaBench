#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  prompt ;
typedef  int /*<<< orphan*/  ai ;
struct TYPE_7__ {scalar_t__ connected; int /*<<< orphan*/  host; } ;
struct TYPE_6__ {int /*<<< orphan*/  cargc; int /*<<< orphan*/  noglobargv; int /*<<< orphan*/  argbuf; int /*<<< orphan*/  cargv; } ;
typedef  TYPE_1__ ArgvInfo ;

/* Variables and functions */
 int /*<<< orphan*/  AddHistory (char*) ; 
 int /*<<< orphan*/  BackToTop ; 
 int /*<<< orphan*/  CloseHost () ; 
 scalar_t__ DoCommand (TYPE_1__*) ; 
 int /*<<< orphan*/  FTPShutdownHost (TYPE_3__*) ; 
 int /*<<< orphan*/  MB_OK ; 
 int MakeArgv (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MakePrompt (char*,int) ; 
 int /*<<< orphan*/  MessageBeep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NcSignal (scalar_t__,int /*<<< orphan*/ ) ; 
 char* Readline (char*) ; 
 scalar_t__ SIGALRM ; 
 scalar_t__ SIGINT ; 
 scalar_t__ SIGPIPE ; 
 int /*<<< orphan*/  SetXtermTitle (char*,...) ; 
 int /*<<< orphan*/  Trace (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gBackToTopJmp ; 
 scalar_t__ gCancelCtrl ; 
 TYPE_3__ gConn ; 
 scalar_t__ gDoneApplication ; 
 int /*<<< orphan*/  gEventNumber ; 
 scalar_t__ gGotSig ; 
 int gMayBackToTopJmp ; 
 int gRunningCommand ; 
 scalar_t__ kBeepAfterCmdTime ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int setjmp (int /*<<< orphan*/ ) ; 
 int sigsetjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 

void
CommandShell(void)
{
	int tUsed, bUsed;
	ArgvInfo ai;
	char prompt[64];
	char *lineRead;
#if defined(WIN32) || defined(_WINDOWS)
#else
	int sj;
#endif
	time_t cmdStart, cmdStop;

	/* Execution may jump back to this point to restart the shell. */
#if defined(WIN32) || defined(_WINDOWS)

#elif defined(HAVE_SIGSETJMP)
	sj = sigsetjmp(gBackToTopJmp, 1);
#else	/* HAVE_SIGSETJMP */
	sj = setjmp(gBackToTopJmp);
#endif	/* HAVE_SIGSETJMP */

#if defined(WIN32) || defined(_WINDOWS)
#else
	if (sj != 0) {
		Trace(0, "Caught signal %d, back at top.\n", gGotSig);
		if (gGotSig == SIGALRM) {
			(void) printf("\nRemote host was not responding, closing down the session.");
			FTPShutdownHost(&gConn);
		} else{
			(void) printf("\nInterrupted.\n");
			if (gCancelCtrl != 0) {
				gCancelCtrl = 0;
				(void) printf("Closing down the current FTP session: ");
				FTPShutdownHost(&gConn);
				(void) sleep(1);
				(void) printf("done.\n");
			}
		}
	}

	gMayBackToTopJmp = 1;
#endif


	++gEventNumber;

	while (gDoneApplication == 0) {
#if defined(WIN32) || defined(_WINDOWS)
#else
		(void) NcSignal(SIGINT, BackToTop);
		(void) NcSignal(SIGPIPE, BackToTop);
		(void) NcSignal(SIGALRM, BackToTop);
#endif

		MakePrompt(prompt, sizeof(prompt));

		if (gConn.connected == 0) {
			SetXtermTitle("DEFAULT");
		} else {
			SetXtermTitle("%s - NcFTP", gConn.host);
		}

		lineRead = Readline(prompt);
		if (lineRead == NULL) {
			/* EOF, Control-D */
			(void) printf("\n");
			break;
		}
		Trace(0, "> %s\n", lineRead);
		AddHistory(lineRead);
		for (tUsed = 0;;) {
			(void) memset(&ai, 0, sizeof(ai));
			bUsed = MakeArgv(lineRead + tUsed, &ai.cargc, ai.cargv,
				(int) (sizeof(ai.cargv) / sizeof(char *)),
				ai.argbuf, sizeof(ai.argbuf),
				ai.noglobargv, 0);
			if (bUsed <= 0)
				break;
			tUsed += bUsed;
			if (ai.cargc == 0)
				continue;
			gRunningCommand = 1;
			(void) time(&cmdStart);
			if (DoCommand(&ai) < 0) {
				(void) time(&cmdStop);
				gRunningCommand = 0;
				break;
			}
			(void) time(&cmdStop);
			gRunningCommand = 0;
			if ((cmdStop - cmdStart) > kBeepAfterCmdTime) {
				/* Let the user know that a time-consuming
				 * operation has completed.
				 */
#if defined(WIN32) || defined(_WINDOWS)
				MessageBeep(MB_OK);
#else
				(void) fprintf(stderr, "\007");
#endif
			}
			++gEventNumber;
		}

		free(lineRead);
	}

	CloseHost();
	gMayBackToTopJmp = 0;
}