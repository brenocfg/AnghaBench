#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {char const* const magic; void* errNo; } ;
struct TYPE_14__ {TYPE_1__* first; } ;
struct TYPE_15__ {TYPE_2__ msg; } ;
struct TYPE_13__ {char* line; } ;
typedef  TYPE_3__* ResponsePtr ;
typedef  TYPE_4__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  DoneWithResponse (TYPE_4__* const,TYPE_3__*) ; 
 int /*<<< orphan*/  Error (TYPE_4__* const,int /*<<< orphan*/ ,char*) ; 
 int FTPGetCWD (TYPE_4__* const,char* const,size_t const) ; 
 TYPE_3__* InitResponse () ; 
 int RCmd (TYPE_4__* const,TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  Strncpy (char* const,char*,size_t const) ; 
 int /*<<< orphan*/  kDontPerror ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 void* kErrCWDFailed ; 
 void* kErrInvalidDirParam ; 
 void* kErrMallocFailed ; 
 char* kLibraryMagic ; 
 int kNoErr ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char const* const,char*) ; 
 char* strrchr (char*,char) ; 

int
FTPChdirAndGetCWD(const FTPCIPtr cip, const char *const cdCwd, char *const newCwd, const size_t newCwdSize)
{
	ResponsePtr rp;
	char *l, *r;
	int result;

	if (cip == NULL)
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);

	if ((newCwd == NULL) || (cdCwd == NULL)) {
		result = kErrInvalidDirParam;
		cip->errNo = kErrInvalidDirParam;
	} else {
		if (cdCwd[0] == '\0') {	/* But allow FTPChdir(cip, ".") to go through. */
			result = FTPGetCWD(cip, newCwd, newCwdSize);
			return (result);
		}
		rp = InitResponse();
		if (rp == NULL) {
			result = kErrMallocFailed;
			cip->errNo = kErrMallocFailed;
			Error(cip, kDontPerror, "Malloc failed.\n");
		} else {
			if (strcmp(cdCwd, "..") == 0)
				result = RCmd(cip, rp, "CDUP");
			else
				result = RCmd(cip, rp, "CWD %s", cdCwd);
			if (result == 2) {
				l = strchr(rp->msg.first->line, '"');
				if ((l == rp->msg.first->line) && ((r = strrchr(rp->msg.first->line, '"')) != NULL) && (l != r)) {
					/* "xxxx" is current directory.
					 * Strip out just the xxxx to copy into the remote cwd.
					 *
					 * This is nice because we didn't have to do a PWD.
					 */
					*r = '\0';
					++l;
					(void) Strncpy(newCwd, l, newCwdSize);
					*r = '"';	/* Restore, so response prints correctly. */
					DoneWithResponse(cip, rp);
					result = kNoErr;
				} else {
					DoneWithResponse(cip, rp);
					result = FTPGetCWD(cip, newCwd, newCwdSize);
				}
			} else if (result > 0) {
				result = kErrCWDFailed;
				cip->errNo = kErrCWDFailed;
				DoneWithResponse(cip, rp);
			} else {
				DoneWithResponse(cip, rp);
			}
		}
	}
	return (result);
}