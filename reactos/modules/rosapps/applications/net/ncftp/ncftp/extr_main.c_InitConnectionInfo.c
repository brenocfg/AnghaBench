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
struct TYPE_3__ {char* host; int leavePass; int maxDials; int redialDelay; char* asciiFilenameExtensions; int /*<<< orphan*/  dataSocketSBufSize; int /*<<< orphan*/  dataSocketRBufSize; int /*<<< orphan*/  dataPortMode; int /*<<< orphan*/  ctrlTimeout; int /*<<< orphan*/  xferTimeout; int /*<<< orphan*/  connTimeout; int /*<<< orphan*/ * progress; int /*<<< orphan*/  user; int /*<<< orphan*/  errLog; int /*<<< orphan*/ * debugLog; } ;

/* Variables and functions */
 int FTPInitConnectionInfo (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* FTPStrError (int) ; 
 scalar_t__ ISTREQ (char*,char*) ; 
 int /*<<< orphan*/  STRNCPY (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SetDebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UseTrace () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 char* gAutoAscii ; 
 TYPE_1__ gConn ; 
 int /*<<< orphan*/  gConnTimeout ; 
 int /*<<< orphan*/  gCtrlTimeout ; 
 int /*<<< orphan*/  gDataPortMode ; 
 int /*<<< orphan*/  gDebug ; 
 int /*<<< orphan*/  gLib ; 
 char* gPrevRemoteCWD ; 
 int gRedialDelay ; 
 int /*<<< orphan*/  gSOBufsize ; 
 int /*<<< orphan*/  gTransferType ; 
 scalar_t__ gTransferTypeInitialized ; 
 scalar_t__ gUnprocessedJobs ; 
 int /*<<< orphan*/  gXferTimeout ; 
 int /*<<< orphan*/  kDefaultFTPBufSize ; 
 int /*<<< orphan*/  kTypeBinary ; 
 int /*<<< orphan*/  stderr ; 

void
InitConnectionInfo(void)
{
	int result;

	result = FTPInitConnectionInfo(&gLib, &gConn, kDefaultFTPBufSize);
	if (result < 0) {
		(void) fprintf(stderr, "ncftp: init connection info error %d (%s).\n", result, FTPStrError(result));
		exit(1);
	}

	gConn.debugLog = NULL;
	gConn.errLog = stderr;
	SetDebug(gDebug);
	UseTrace();
	(void) STRNCPY(gConn.user, "anonymous");
	gConn.host[0] = '\0';
	gConn.progress = NULL;
	gTransferTypeInitialized = 0;
	gTransferType = kTypeBinary;
	gConn.leavePass = 1;		/* Don't let the lib zap it. */
	gConn.connTimeout = gConnTimeout;
	gConn.xferTimeout = gXferTimeout;
	gConn.ctrlTimeout = gCtrlTimeout;
	gConn.dataPortMode = gDataPortMode;
	gConn.maxDials = (-1);	/* Dial forever, until they hit ^C. */
	gUnprocessedJobs = 0;
	gPrevRemoteCWD[0] = '\0';
	gConn.dataSocketRBufSize = gConn.dataSocketSBufSize = gSOBufsize;
	if (gRedialDelay >= 10)
		gConn.redialDelay = gRedialDelay;
	if ((gAutoAscii[0] == '\0') || (ISTREQ(gAutoAscii, "no")) || (ISTREQ(gAutoAscii, "off")) || (ISTREQ(gAutoAscii, "false"))) {
		gConn.asciiFilenameExtensions = NULL;
	} else {
		gConn.asciiFilenameExtensions = gAutoAscii;
	}
}