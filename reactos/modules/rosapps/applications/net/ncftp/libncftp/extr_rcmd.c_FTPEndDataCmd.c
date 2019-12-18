#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int errNo; int /*<<< orphan*/  magic; } ;
struct TYPE_11__ {int codeType; } ;
typedef  TYPE_1__* ResponsePtr ;
typedef  TYPE_2__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  CloseDataConnection (TYPE_2__* const) ; 
 int /*<<< orphan*/  DoneWithResponse (TYPE_2__* const,TYPE_1__*) ; 
 int /*<<< orphan*/  Error (TYPE_2__* const,int /*<<< orphan*/ ,char*) ; 
 int GetResponse (TYPE_2__* const,TYPE_1__*) ; 
 TYPE_1__* InitResponse () ; 
 int /*<<< orphan*/  kDontPerror ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 int kErrDataTransferFailed ; 
 int kErrMallocFailed ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 int kNoErr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
FTPEndDataCmd(const FTPCIPtr cip, int didXfer)
{
	int result;
	int respCode;
	ResponsePtr rp;

	if (cip == NULL)
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);

	CloseDataConnection(cip);
	result = kNoErr;
	if (didXfer) {
		/* Get the response to the data transferred.  Most likely a message
		 * saying that the transfer completed succesfully.  However, if
		 * we tried to abort the transfer using ABOR, we will have a response
		 * to that command instead.
		 */
		rp = InitResponse();
		if (rp == NULL) {
			Error(cip, kDontPerror, "Malloc failed.\n");
			cip->errNo = kErrMallocFailed;
			result = cip->errNo;
			return (result);
		}
		result = GetResponse(cip, rp);
		if (result < 0)
			return (result);
		respCode = rp->codeType;
		DoneWithResponse(cip, rp);
		if (respCode != 2) {
			cip->errNo = kErrDataTransferFailed;
			result = cip->errNo;
		} else {
			result = kNoErr;
		}
	}
	return (result);
}