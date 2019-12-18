#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* errNo; int /*<<< orphan*/  magic; } ;
struct TYPE_10__ {int /*<<< orphan*/  msg; } ;
typedef  TYPE_1__* ResponsePtr ;
typedef  int /*<<< orphan*/ * LineListPtr ;
typedef  TYPE_2__* FTPCIPtr ;

/* Variables and functions */
 scalar_t__ CopyLineList (int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DoneWithResponse (TYPE_2__* const,TYPE_1__*) ; 
 int /*<<< orphan*/  Error (TYPE_2__* const,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  InitLineList (int /*<<< orphan*/ * const) ; 
 TYPE_1__* InitResponse () ; 
 int RCmd (TYPE_2__* const,TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  kDontPerror ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 void* kErrHELPFailed ; 
 void* kErrMallocFailed ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 int kNoErr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
FTPRemoteHelp(const FTPCIPtr cip, const char *const pattern, const LineListPtr llp)
{
	int result;
	ResponsePtr rp;

	if ((cip == NULL) || (llp == NULL))
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);

	InitLineList(llp);
	rp = InitResponse();
	if (rp == NULL) {
		result = kErrMallocFailed;
		cip->errNo = kErrMallocFailed;
		Error(cip, kDontPerror, "Malloc failed.\n");
	} else {
		if ((pattern == NULL) || (*pattern == '\0'))
			result = RCmd(cip, rp, "HELP");
		else
			result = RCmd(cip, rp, "HELP %s", pattern);
		if (result < 0) {
			DoneWithResponse(cip, rp);
			return (result);
		} else if (result == 2) {
			if (CopyLineList(llp, &rp->msg) < 0) {
				result = kErrMallocFailed;
				cip->errNo = kErrMallocFailed;
				Error(cip, kDontPerror, "Malloc failed.\n");
			} else {
				result = kNoErr;
			}
		} else {
			cip->errNo = kErrHELPFailed;
			result = kErrHELPFailed;
		}
		DoneWithResponse(cip, rp);
	}
	return (result);
}