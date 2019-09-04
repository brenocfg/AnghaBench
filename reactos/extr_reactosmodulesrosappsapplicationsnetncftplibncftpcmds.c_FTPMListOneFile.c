#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ hasMLST; scalar_t__ serverType; int ietfCompatLevel; int errNo; } ;
struct TYPE_15__ {TYPE_2__* first; } ;
struct TYPE_16__ {int /*<<< orphan*/  code; TYPE_3__ msg; } ;
struct TYPE_14__ {TYPE_1__* next; int /*<<< orphan*/ * line; } ;
struct TYPE_13__ {int /*<<< orphan*/ * line; } ;
typedef  TYPE_4__* ResponsePtr ;
typedef  int /*<<< orphan*/  MLstItemPtr ;
typedef  TYPE_5__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  DoneWithResponse (TYPE_5__* const,TYPE_4__*) ; 
 int /*<<< orphan*/  Error (TYPE_5__* const,int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* InitResponse () ; 
 int RCmd (TYPE_5__* const,TYPE_4__*,char*,char const* const) ; 
 scalar_t__ UNIMPLEMENTED_CMD (int /*<<< orphan*/ ) ; 
 int UnMlsT (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 scalar_t__ kCommandNotAvailable ; 
 int /*<<< orphan*/  kDontPerror ; 
 int kErrInvalidMLSTResponse ; 
 void* kErrMLSTFailed ; 
 void* kErrMLSTNotAvailable ; 
 int kErrMallocFailed ; 
 scalar_t__ kServerTypeNcFTPd ; 
 scalar_t__ kServerTypeRoxen ; 

int
FTPMListOneFile(const FTPCIPtr cip, const char *const file, const MLstItemPtr mlip)
{
	int result;
	ResponsePtr rp;

	/* We do a special check for older versions of NcFTPd which
	 * are based off of an incompatible previous version of IETF
	 * extensions.
	 *
	 * Roxen also seems to be way outdated, where MLST was on the
	 * data connection among other things.
	 *
	 */
	if (
		(cip->hasMLST == kCommandNotAvailable) ||
		((cip->serverType == kServerTypeNcFTPd) && (cip->ietfCompatLevel < 19981201)) ||
		(cip->serverType == kServerTypeRoxen)
	) {
		cip->errNo = kErrMLSTNotAvailable;
		return (cip->errNo);
	}

	rp = InitResponse();
	if (rp == NULL) {
		result = cip->errNo = kErrMallocFailed;
		Error(cip, kDontPerror, "Malloc failed.\n");
	} else {
		result = RCmd(cip, rp, "MLST %s", file);
		if (
			(result == 2) &&
			(rp->msg.first->line != NULL) &&
			(rp->msg.first->next != NULL) &&
			(rp->msg.first->next->line != NULL)
		) {
			result = UnMlsT(rp->msg.first->next->line, mlip);
			if (result < 0) {
				cip->errNo = result = kErrInvalidMLSTResponse;
			}
		} else if (UNIMPLEMENTED_CMD(rp->code)) {
			cip->hasMLST = kCommandNotAvailable;
			cip->errNo = kErrMLSTNotAvailable;
			result = kErrMLSTNotAvailable;
		} else {
			cip->errNo = kErrMLSTFailed;
			result = kErrMLSTFailed;
		}
		DoneWithResponse(cip, rp);
	}

	return (result);
}