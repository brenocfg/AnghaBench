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
struct TYPE_3__ {char* buf; int errNo; void* ctrlSocketW; void* ctrlSocketR; int /*<<< orphan*/ * cin; scalar_t__ ctrlTimeout; int /*<<< orphan*/  srlBuf; int /*<<< orphan*/  ctrlSrl; int /*<<< orphan*/ * cout; int /*<<< orphan*/  bufSize; int /*<<< orphan*/  lastFTPCmdResultLL; int /*<<< orphan*/ * asciiFilenameExtensions; int /*<<< orphan*/ * startingWorkingDirectory; int /*<<< orphan*/ * passphraseProc; int /*<<< orphan*/ * onLoginMsgProc; int /*<<< orphan*/ * printResponseProc; int /*<<< orphan*/ * redialStatusProc; int /*<<< orphan*/ * onConnectMsgProc; int /*<<< orphan*/ * lname; int /*<<< orphan*/ * rname; int /*<<< orphan*/ * progress; int /*<<< orphan*/ * errLogProc; int /*<<< orphan*/ * debugLogProc; int /*<<< orphan*/ * errLog; int /*<<< orphan*/ * debugLog; int /*<<< orphan*/  lip; } ;
typedef  int /*<<< orphan*/  LineList ;
typedef  int /*<<< orphan*/  FTPLIPtr ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  CloseFile (int /*<<< orphan*/ **) ; 
 scalar_t__ InitSReadlineInfo (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int,int,int) ; 
 void* _fdopen (void*,char*) ; 
 scalar_t__ calloc (size_t,int /*<<< orphan*/ ) ; 
 void* kClosedFileDescriptor ; 
 int kErrFdopenR ; 
 int kErrFdopenW ; 
 int kErrMallocFailed ; 
 int kNoErr ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
FTPRebuildConnectionInfo(const FTPLIPtr lip, const FTPCIPtr cip)
{
	char *buf;

	cip->lip = lip;
	cip->debugLog = NULL;
	cip->errLog = NULL;
	cip->debugLogProc = NULL;
	cip->errLogProc = NULL;
	cip->buf = NULL;
	cip->cin = NULL;
	cip->cout = NULL;
	cip->errNo = 0;
	cip->progress = NULL;
	cip->rname = NULL;
	cip->lname = NULL;
	cip->onConnectMsgProc = NULL;
	cip->redialStatusProc = NULL;
	cip->printResponseProc = NULL;
	cip->onLoginMsgProc = NULL;
	cip->passphraseProc = NULL;
	cip->startingWorkingDirectory = NULL;
	cip->asciiFilenameExtensions = NULL;

	(void) memset(&cip->lastFTPCmdResultLL, 0, sizeof(LineList));

	/* Allocate a new buffer. */
	buf = (char *) calloc((size_t) 1, cip->bufSize);
	if (buf == NULL) {
		cip->errNo = kErrMallocFailed;
		return (kErrMallocFailed);
	}
	cip->buf = buf;

	/* Reattach the FILE pointers for use with the Std I/O library
	 * routines.
	 */
	if ((cip->cin = _fdopen(cip->ctrlSocketR, "r")) == NULL) {
		cip->errNo = kErrFdopenR;
		cip->ctrlSocketR = kClosedFileDescriptor;
		cip->ctrlSocketW = kClosedFileDescriptor;
		return (kErrFdopenR);
	}

	if ((cip->cout = _fdopen(cip->ctrlSocketW, "w")) == NULL) {
		CloseFile(&cip->cin);
		cip->errNo = kErrFdopenW;
		cip->ctrlSocketR = kClosedFileDescriptor;
		cip->ctrlSocketW = kClosedFileDescriptor;
		return (kErrFdopenW);
	}

#if USE_SIO
	if (InitSReadlineInfo(&cip->ctrlSrl, cip->ctrlSocketR, cip->srlBuf, sizeof(cip->srlBuf), (int) cip->ctrlTimeout, 1) < 0) {
		cip->errNo = kErrFdopenW;
		CloseFile(&cip->cin);
		cip->errNo = kErrFdopenW;
		cip->ctrlSocketR = kClosedFileDescriptor;
		cip->ctrlSocketW = kClosedFileDescriptor;
		return (kErrFdopenW);
	}
#endif
	return (kNoErr);
}