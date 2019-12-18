#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* magic; int errNo; char* buf; int bufSize; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int FTPChdir (TYPE_1__*,char const* const) ; 
 int FTPChdirAndGetCWD (TYPE_1__*,char const* const,char* const,size_t const) ; 
 int FTPCmd (TYPE_1__*,char*,char*) ; 
 int FTPGetCWD (TYPE_1__*,char* const,size_t const) ; 
 int FTPMkdir (TYPE_1__*,char const* const,int /*<<< orphan*/ ) ; 
 char* StrFindLocalPathDelim (char*) ; 
 int /*<<< orphan*/  Strncpy (char*,char const* const,int) ; 
 int kChdirAndGetCWD ; 
 int kChdirAndMkdir ; 
 int kChdirOnly ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 void* kErrInvalidDirParam ; 
 char* kLibraryMagic ; 
 int kNoErr ; 
 int /*<<< orphan*/  kRecursiveYes ; 
 scalar_t__ strcmp (char const* const,char*) ; 

int
FTPChdir3(FTPCIPtr cip, const char *const cdCwd, char *const newCwd, const size_t newCwdSize, int flags)
{
	char *cp, *startcp;
	int result;
	int lastSubDir;
	int mkd, pwd;

	if (cip == NULL)
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);

	if (cdCwd == NULL) {
		result = kErrInvalidDirParam;
		cip->errNo = kErrInvalidDirParam;
		return result;
	}

	if (flags == kChdirOnly)
		return (FTPChdir(cip, cdCwd));
	if (flags == kChdirAndGetCWD) {
		return (FTPChdirAndGetCWD(cip, cdCwd, newCwd, newCwdSize));
	} else if (flags == kChdirAndMkdir) {
		result = FTPMkdir(cip, cdCwd, kRecursiveYes);
		if (result == kNoErr)
			result = FTPChdir(cip, cdCwd);
		return result;
	} else if (flags == (kChdirAndMkdir|kChdirAndGetCWD)) {
		result = FTPMkdir(cip, cdCwd, kRecursiveYes);
		if (result == kNoErr)
			result = FTPChdirAndGetCWD(cip, cdCwd, newCwd, newCwdSize);
		return result;
	}

	/* else: (flags | kChdirOneSubdirAtATime) == true */

	cp = cip->buf;
	cp[cip->bufSize - 1] = '\0';
	(void) Strncpy(cip->buf, cdCwd, cip->bufSize);
	if (cp[cip->bufSize - 1] != '\0')
		return (kErrBadParameter);

	mkd = (flags & kChdirAndMkdir);
	pwd = (flags & kChdirAndGetCWD);

	if ((cdCwd[0] == '\0') || (strcmp(cdCwd, ".") == 0)) {
		result = 0;
		if (flags == kChdirAndGetCWD)
			result = FTPGetCWD(cip, newCwd, newCwdSize);
		return (result);
	}

	lastSubDir = 0;
	do {
		startcp = cp;
		cp = StrFindLocalPathDelim(cp);
		if (cp != NULL) {
			/* If this is the first slash in an absolute
			 * path, then startcp will be empty.  We will
			 * use this below to treat this as the root
			 * directory.
			 */
			*cp++ = '\0';
		} else {
			lastSubDir = 1;
		}
		if (strcmp(startcp, ".") == 0) {
			result = 0;
			if ((lastSubDir != 0) && (pwd != 0))
				result = FTPGetCWD(cip, newCwd, newCwdSize);
		} else if ((lastSubDir != 0) && (pwd != 0)) {
			result = FTPChdirAndGetCWD(cip, (*startcp != '\0') ? startcp : "/", newCwd, newCwdSize);
		} else {
			result = FTPChdir(cip, (*startcp != '\0') ? startcp : "/");
		}
		if (result < 0) {
			if ((mkd != 0) && (*startcp != '\0')) {
				if (FTPCmd(cip, "MKD %s", startcp) == 2) {
					result = FTPChdir(cip, startcp);
				} else {
					/* couldn't change nor create */
					cip->errNo = result;
				}
			} else {
				cip->errNo = result;
			}
		}
	} while ((!lastSubDir) && (result == 0));

	return (result);
}