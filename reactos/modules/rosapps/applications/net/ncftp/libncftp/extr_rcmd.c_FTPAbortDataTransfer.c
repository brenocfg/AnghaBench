#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ dataSocket; scalar_t__ abortTimeout; int errNo; } ;
typedef  int /*<<< orphan*/ * ResponsePtr ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  CloseDataConnection (TYPE_1__* const) ; 
 int /*<<< orphan*/  DoneWithResponse (TYPE_1__* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Error (TYPE_1__* const,int /*<<< orphan*/ ,char*) ; 
 int FTPCmdNoResponse (TYPE_1__* const,char*) ; 
 int GetResponse (TYPE_1__* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InitResponse () ; 
 int /*<<< orphan*/  PrintF (TYPE_1__* const,char*) ; 
 int /*<<< orphan*/  SendTelnetInterrupt (TYPE_1__* const) ; 
 int /*<<< orphan*/  SetLinger (TYPE_1__* const,scalar_t__,int /*<<< orphan*/ ) ; 
 int WaitResponse (TYPE_1__* const,unsigned int) ; 
 scalar_t__ kClosedFileDescriptor ; 
 int /*<<< orphan*/  kDontPerror ; 
 int kErrMallocFailed ; 
 int kNoErr ; 

void
FTPAbortDataTransfer(const FTPCIPtr cip)
{
	ResponsePtr rp;
	int result;

	if (cip->dataSocket != kClosedFileDescriptor) {
		PrintF(cip, "Starting abort sequence.\n");
		SendTelnetInterrupt(cip);		/* Probably could get by w/o doing this. */

		result = FTPCmdNoResponse(cip, "ABOR");
		if (result != kNoErr) {
			/* Linger could cause close to block, so unset it. */
			(void) SetLinger(cip, cip->dataSocket, 0);
			CloseDataConnection(cip);
			PrintF(cip, "Could not send abort command.\n");
			return;
		}

		if (cip->abortTimeout > 0) {
			result = WaitResponse(cip, (unsigned int) cip->abortTimeout);
			if (result <= 0) {
				/* Error or no response received to ABOR in time. */
				(void) SetLinger(cip, cip->dataSocket, 0);
				CloseDataConnection(cip);
				PrintF(cip, "No response received to abort request.\n");
				return;
			}
		}

		rp = InitResponse();
		if (rp == NULL) {
			Error(cip, kDontPerror, "Malloc failed.\n");
			cip->errNo = kErrMallocFailed;
			result = cip->errNo;
			return;
		}

		result = GetResponse(cip, rp);
		if (result < 0) {
			/* Shouldn't happen, and doesn't matter if it does. */
			(void) SetLinger(cip, cip->dataSocket, 0);
			CloseDataConnection(cip);
			PrintF(cip, "Invalid response to abort request.\n");
			DoneWithResponse(cip, rp);
			return;
		}
		DoneWithResponse(cip, rp);

		/* A response to the abort request has been received.
		 * Now the only thing left to do is close the data
		 * connection, making sure to turn off linger mode
		 * since we don't care about straggling data bits.
		 */
		(void) SetLinger(cip, cip->dataSocket, 0);
		CloseDataConnection(cip);		/* Must close (by protocol). */
		PrintF(cip, "End abort.\n");
	}
}