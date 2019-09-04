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
typedef  scalar_t__ longest_int ;
struct TYPE_11__ {int errNo; int /*<<< orphan*/  hasREST; } ;
struct TYPE_10__ {int /*<<< orphan*/  code; } ;
typedef  TYPE_1__* ResponsePtr ;
typedef  TYPE_2__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  DoneWithResponse (TYPE_2__* const,TYPE_1__*) ; 
 int /*<<< orphan*/  Error (TYPE_2__* const,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* InitResponse () ; 
 int RCmd (TYPE_2__* const,TYPE_1__*,char*,long) ; 
 scalar_t__ UNIMPLEMENTED_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCommandAvailable ; 
 int /*<<< orphan*/  kCommandNotAvailable ; 
 int /*<<< orphan*/  kDontPerror ; 
 int kErrMallocFailed ; 
 int kErrSetStartPoint ; 

int
SetStartOffset(const FTPCIPtr cip, longest_int restartPt)
{
	ResponsePtr rp;
	int result;

	if (restartPt != (longest_int) 0) {
		rp = InitResponse();
		if (rp == NULL) {
			Error(cip, kDontPerror, "Malloc failed.\n");
			cip->errNo = kErrMallocFailed;
			return (cip->errNo);
		}

		/* Force reset to offset zero. */
		if (restartPt == (longest_int) -1)
			restartPt = (longest_int) 0;
#ifdef PRINTF_LONG_LONG
		result = RCmd(cip, rp,
		"REST " PRINTF_LONG_LONG,
		restartPt);
#else
		result = RCmd(cip, rp, "REST %ld", (long) restartPt);
#endif

		if (result < 0) {
			return (result);
		} else if (result == 3) {
			cip->hasREST = kCommandAvailable;
			DoneWithResponse(cip, rp);
		} else if (UNIMPLEMENTED_CMD(rp->code)) {
			cip->hasREST = kCommandNotAvailable;
			DoneWithResponse(cip, rp);
			cip->errNo = kErrSetStartPoint;
			return (kErrSetStartPoint);
		} else {
			DoneWithResponse(cip, rp);
			cip->errNo = kErrSetStartPoint;
			return (kErrSetStartPoint);
		}
	}
	return (0);
}