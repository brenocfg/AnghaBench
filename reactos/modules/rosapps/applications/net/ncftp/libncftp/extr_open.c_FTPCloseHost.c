#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ dataSocket; scalar_t__ connected; int errNo; int eofOkay; int /*<<< orphan*/  magic; } ;
struct TYPE_12__ {int eofOkay; } ;
typedef  TYPE_1__* ResponsePtr ;
typedef  TYPE_2__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  CloseControlConnection (TYPE_2__* const) ; 
 int /*<<< orphan*/  DoneWithResponse (TYPE_2__* const,TYPE_1__*) ; 
 int /*<<< orphan*/  FTPAbortDataTransfer (TYPE_2__* const) ; 
 int /*<<< orphan*/  FTPDeallocateHost (TYPE_2__* const) ; 
 TYPE_1__* InitResponse () ; 
 int /*<<< orphan*/  RCmd (TYPE_2__* const,TYPE_1__*,char*) ; 
 scalar_t__ kClosedFileDescriptor ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 int kErrMallocFailed ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 int kNoErr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
FTPCloseHost(const FTPCIPtr cip)
{
	ResponsePtr rp;
	int result;

	if (cip == NULL)
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);

	/* Data connection shouldn't be open normally. */
	if (cip->dataSocket != kClosedFileDescriptor)
		FTPAbortDataTransfer(cip);

	result = kNoErr;
	if (cip->connected != 0) {
		rp = InitResponse();
		if (rp == NULL) {
			cip->errNo = kErrMallocFailed;
			result = cip->errNo;
		} else {
			rp->eofOkay = 1;	/* We are expecting EOF after this cmd. */
			cip->eofOkay = 1;
			(void) RCmd(cip, rp, "QUIT");
			DoneWithResponse(cip, rp);
		}
	}

	CloseControlConnection(cip);

	/* Dispose dynamic data structures, so you won't leak
	 * if you OpenHost with this again.
	 */
	FTPDeallocateHost(cip);
	return (result);
}