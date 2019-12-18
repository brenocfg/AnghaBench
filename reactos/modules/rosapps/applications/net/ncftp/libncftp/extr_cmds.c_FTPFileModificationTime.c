#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_15__ {scalar_t__ hasMDTM; void* errNo; int /*<<< orphan*/  magic; } ;
struct TYPE_13__ {TYPE_1__* first; } ;
struct TYPE_14__ {int /*<<< orphan*/  code; TYPE_2__ msg; } ;
struct TYPE_12__ {int /*<<< orphan*/  line; } ;
typedef  TYPE_3__* ResponsePtr ;
typedef  TYPE_4__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  DoneWithResponse (TYPE_4__* const,TYPE_3__*) ; 
 int /*<<< orphan*/  Error (TYPE_4__* const,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* InitResponse () ; 
 int RCmd (TYPE_4__* const,TYPE_3__*,char*,char const* const) ; 
 scalar_t__ UNIMPLEMENTED_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnMDTMDate (int /*<<< orphan*/ ) ; 
 scalar_t__ kCommandAvailable ; 
 scalar_t__ kCommandNotAvailable ; 
 int /*<<< orphan*/  kDontPerror ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 void* kErrMDTMFailed ; 
 void* kErrMDTMNotAvailable ; 
 void* kErrMallocFailed ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 int /*<<< orphan*/  kModTimeUnknown ; 
 int kNoErr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

int
FTPFileModificationTime(const FTPCIPtr cip, const char *const file, time_t *const mdtm)
{
	int result;
	ResponsePtr rp;

	if (cip == NULL)
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);

	if ((mdtm == NULL) || (file == NULL))
		return (kErrBadParameter);
	*mdtm = kModTimeUnknown;

	if (cip->hasMDTM == kCommandNotAvailable) {
		cip->errNo = kErrMDTMNotAvailable;
		result = kErrMDTMNotAvailable;
	} else {
		rp = InitResponse();
		if (rp == NULL) {
			result = kErrMallocFailed;
			cip->errNo = kErrMallocFailed;
			Error(cip, kDontPerror, "Malloc failed.\n");
		} else {
			result = RCmd(cip, rp, "MDTM %s", file);
			if (result < 0) {
				DoneWithResponse(cip, rp);
				return (result);
			} else if (strncmp(rp->msg.first->line, "19100", 5) == 0) {
				Error(cip, kDontPerror, "Warning: Server has Y2K Bug in \"MDTM\" command.\n");
				cip->errNo = kErrMDTMFailed;
				result = kErrMDTMFailed;
			} else if (result == 2) {
				*mdtm = UnMDTMDate(rp->msg.first->line);
				cip->hasMDTM = kCommandAvailable;
				result = kNoErr;
			} else if (UNIMPLEMENTED_CMD(rp->code)) {
				cip->hasMDTM = kCommandNotAvailable;
				cip->errNo = kErrMDTMNotAvailable;
				result = kErrMDTMNotAvailable;
			} else {
				cip->errNo = kErrMDTMFailed;
				result = kErrMDTMFailed;
			}
			DoneWithResponse(cip, rp);
		}
	}
	return (result);
}