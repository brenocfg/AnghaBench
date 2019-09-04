#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  savedCwd ;
struct TYPE_26__ {scalar_t__ STATfileParamWorks; int errNo; char* startingWorkingDirectory; int /*<<< orphan*/  magic; } ;
struct TYPE_25__ {TYPE_1__* last; } ;
struct TYPE_23__ {int nLines; TYPE_3__* first; } ;
struct TYPE_24__ {TYPE_4__ msg; } ;
struct TYPE_22__ {TYPE_2__* next; } ;
struct TYPE_21__ {int /*<<< orphan*/ * line; } ;
struct TYPE_20__ {char const* line; } ;
typedef  TYPE_5__* ResponsePtr ;
typedef  TYPE_6__ LineList ;
typedef  TYPE_7__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  DisposeLineListContents (TYPE_6__*) ; 
 int /*<<< orphan*/  DoneWithResponse (TYPE_7__* const,TYPE_5__*) ; 
 int /*<<< orphan*/  Error (TYPE_7__* const,int /*<<< orphan*/ ,char*) ; 
 int FTPChdir (TYPE_7__* const,char*) ; 
 int FTPGetCWD (TYPE_7__* const,char*,int) ; 
 int FTPListToMemory2 (TYPE_7__* const,char*,TYPE_6__*,char*,int /*<<< orphan*/ ,int*) ; 
 TYPE_5__* InitResponse () ; 
 int RCmd (TYPE_7__* const,TYPE_5__*,char*,char const* const) ; 
 scalar_t__ kCommandAvailabilityUnknown ; 
 scalar_t__ kCommandAvailable ; 
 scalar_t__ kCommandNotAvailable ; 
 int /*<<< orphan*/  kDontPerror ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 void* kErrMallocFailed ; 
 void* kErrSTATFailed ; 
 int kErrSTATwithFileNotAvailable ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 int kNoErr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ *,char*) ; 

int
FTPFileExistsStat(const FTPCIPtr cip, const char *const file)
{
	int result;
	ResponsePtr rp;
	LineList fileList;
	char savedCwd[512];

	if (cip == NULL)
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);

	if (file == NULL)
		return (kErrBadParameter);

	if (cip->STATfileParamWorks == kCommandNotAvailable) {
		cip->errNo = result = kErrSTATwithFileNotAvailable;
		return (result);
	}

	if (cip->STATfileParamWorks == kCommandAvailabilityUnknown) {
		rp = InitResponse();
		if (rp == NULL) {
			result = kErrMallocFailed;
			cip->errNo = kErrMallocFailed;
			Error(cip, kDontPerror, "Malloc failed.\n");
			return (result);

		}

		/* First, make sure that when we STAT a pathname
		 * that does not exist, that we get an error back.
		 *
		 * We also assume that a valid STAT response has
		 * at least 3 lines of response text, typically
		 * a "start" line, intermediate data, and then
		 * a trailing line.
		 *
		 * We also can see a one-line case.
		 */
		result = RCmd(cip, rp, "STAT %s", "NoSuchFile");
		if ((result == 2) && ((rp->msg.nLines >= 3) || (rp->msg.nLines == 1))) {
			/* Hmmm.... it gave back a positive
			 * response.  So STAT <file> does not
			 * work correctly.
			 */
			if (
				(rp->msg.first->next != NULL) &&
				(rp->msg.first->next->line != NULL) &&
				(
					(strstr(rp->msg.first->next->line, "o such file") != NULL) ||
					(strstr(rp->msg.first->next->line, "ot found") != NULL)
				)
			) {
				/* OK, while we didn't want a 200
				 * level response, some servers,
				 * like wu-ftpd print an error
				 * message "No such file or
				 * directory" which we can special
				 * case.
				 */
				result = kNoErr;
			} else {
				cip->STATfileParamWorks = kCommandNotAvailable;
				cip->errNo = result = kErrSTATwithFileNotAvailable;
				DoneWithResponse(cip, rp);
				return (result);
			}
		}
		DoneWithResponse(cip, rp);

		/* We can't assume that we can simply say STAT rootdir/firstfile,
		 * since the remote host may not be using / as a directory
		 * delimiter.  So we have to change to the root directory
		 * and then do the STAT on that file.
		 */
		if (
			(FTPGetCWD(cip, savedCwd, sizeof(savedCwd)) != kNoErr) ||
			(FTPChdir(cip, cip->startingWorkingDirectory) != kNoErr)
		) {
			return (cip->errNo);
		}

		/* OK, we get an error when we stat
		 * a non-existant file, but now we need to
		 * see if we get a positive reply when
		 * we stat a file that does exist.
		 *
		 * To do this, we list the root directory,
		 * which we assume has one or more items.
		 * If it doesn't, the user can't do anything
		 * anyway.  Then we stat the first item
		 * we found to see if STAT says it exists.
		 */
		if (
			((result = FTPListToMemory2(cip, "", &fileList, "", 0, (int *) 0)) < 0) ||
			(fileList.last == NULL) ||
			(fileList.last->line == NULL)
		) {
			/* Hmmm... well, in any case we can't use STAT. */
			cip->STATfileParamWorks = kCommandNotAvailable;
			cip->errNo = result = kErrSTATwithFileNotAvailable;
			DisposeLineListContents(&fileList);
			(void) FTPChdir(cip, savedCwd);
			return (result);
		}

		rp = InitResponse();
		if (rp == NULL) {
			result = kErrMallocFailed;
			cip->errNo = kErrMallocFailed;
			Error(cip, kDontPerror, "Malloc failed.\n");
			DisposeLineListContents(&fileList);
			(void) FTPChdir(cip, savedCwd);
			return (result);

		}

		result = RCmd(cip, rp, "STAT %s", fileList.last->line);
		DisposeLineListContents(&fileList);

		if ((result != 2) || (rp->msg.nLines == 2)) {
			/* Hmmm.... it gave back a negative
			 * response.  So STAT <file> does not
			 * work correctly.
			 */
			cip->STATfileParamWorks = kCommandNotAvailable;
			cip->errNo = result = kErrSTATwithFileNotAvailable;
			DoneWithResponse(cip, rp);
			(void) FTPChdir(cip, savedCwd);
			return (result);
		} else if (
				(rp->msg.first->next != NULL) &&
				(rp->msg.first->next->line != NULL) &&
				(
					(strstr(rp->msg.first->next->line, "o such file") != NULL) ||
					(strstr(rp->msg.first->next->line, "ot found") != NULL)
				)
		) {
			/* Same special-case of the second line of STAT response. */
			cip->STATfileParamWorks = kCommandNotAvailable;
			cip->errNo = result = kErrSTATwithFileNotAvailable;
			DoneWithResponse(cip, rp);
			(void) FTPChdir(cip, savedCwd);
			return (result);
		}
		DoneWithResponse(cip, rp);
		cip->STATfileParamWorks = kCommandAvailable;

		/* Don't forget to change back to the original directory. */
		(void) FTPChdir(cip, savedCwd);
	}

	rp = InitResponse();
	if (rp == NULL) {
		result = kErrMallocFailed;
		cip->errNo = kErrMallocFailed;
		Error(cip, kDontPerror, "Malloc failed.\n");
		return (result);
	}

	result = RCmd(cip, rp, "STAT %s", file);
	if (result == 2) {
		result = kNoErr;
		if (((rp->msg.nLines >= 3) || (rp->msg.nLines == 1))) {
			if (
				(rp->msg.first->next != NULL) &&
				(rp->msg.first->next->line != NULL) &&
				(
					(strstr(rp->msg.first->next->line, "o such file") != NULL) ||
					(strstr(rp->msg.first->next->line, "ot found") != NULL)
				)
			) {
				cip->errNo = kErrSTATFailed;
				result = kErrSTATFailed;
			} else {
				result = kNoErr;
			}
		} else if (rp->msg.nLines == 2) {
			cip->errNo = kErrSTATFailed;
			result = kErrSTATFailed;
		} else {
			result = kNoErr;
		}
	} else {
		cip->errNo = kErrSTATFailed;
		result = kErrSTATFailed;
	}
	DoneWithResponse(cip, rp);
	return (result);
}