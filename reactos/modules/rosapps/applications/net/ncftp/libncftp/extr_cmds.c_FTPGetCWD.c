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
struct TYPE_15__ {void* errNo; int /*<<< orphan*/  magic; } ;
struct TYPE_13__ {TYPE_1__* first; } ;
struct TYPE_14__ {TYPE_2__ msg; } ;
struct TYPE_12__ {char* line; } ;
typedef  TYPE_3__* ResponsePtr ;
typedef  TYPE_4__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  DoneWithResponse (TYPE_4__* const,TYPE_3__*) ; 
 int /*<<< orphan*/  Error (TYPE_4__* const,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* InitResponse () ; 
 int RCmd (TYPE_4__* const,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  Strncpy (char* const,char*,size_t const) ; 
 int /*<<< orphan*/  kDontPerror ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 void* kErrInvalidDirParam ; 
 void* kErrMallocFailed ; 
 void* kErrPWDFailed ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 int kNoErr ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

int
FTPGetCWD(const FTPCIPtr cip, char *const newCwd, const size_t newCwdSize)
{
	ResponsePtr rp;
	char *l, *r;
	int result;

	if (cip == NULL)
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);

	if ((newCwd == NULL) || (newCwdSize == 0)) {
		result = kErrInvalidDirParam;
		cip->errNo = kErrInvalidDirParam;
	} else {
		rp = InitResponse();
		if (rp == NULL) {
			result = kErrMallocFailed;
			cip->errNo = kErrMallocFailed;
			Error(cip, kDontPerror, "Malloc failed.\n");
		} else {
			result = RCmd(cip, rp, "PWD");
			if (result == 2) {
				if ((r = strrchr(rp->msg.first->line, '"')) != NULL) {
					/* "xxxx" is current directory.
					 * Strip out just the xxxx to copy into the remote cwd.
					 */
					l = strchr(rp->msg.first->line, '"');
					if ((l != NULL) && (l != r)) {
						*r = '\0';
						++l;
						(void) Strncpy(newCwd, l, newCwdSize);
						*r = '"';	/* Restore, so response prints correctly. */
					}
				} else {
					/* xxxx is current directory.
					 * Mostly for VMS.
					 */
					if ((r = strchr(rp->msg.first->line, ' ')) != NULL) {
						*r = '\0';
						(void) Strncpy(newCwd, (rp->msg.first->line), newCwdSize);
						*r = ' ';	/* Restore, so response prints correctly. */
					}
				}
				result = kNoErr;
			} else if (result > 0) {
				result = kErrPWDFailed;
				cip->errNo = kErrPWDFailed;
			}
			DoneWithResponse(cip, rp);
		}
	}
	return (result);
}