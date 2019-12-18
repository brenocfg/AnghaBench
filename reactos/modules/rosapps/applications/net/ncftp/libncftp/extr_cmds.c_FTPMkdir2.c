#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int errNo; char const* const buf; int /*<<< orphan*/  lastFTPCmdResultStr; int /*<<< orphan*/  bufSize; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  Error (TYPE_1__* const,int /*<<< orphan*/ ,char*,char const* const,char*,...) ; 
 int FTPChdir (TYPE_1__* const,char const* const) ; 
 int FTPCmd (TYPE_1__* const,char*,char const* const) ; 
 int /*<<< orphan*/  FTPGetCWD (TYPE_1__* const,char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRNCPY (char*,char const* const) ; 
 int /*<<< orphan*/  kDontPerror ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 void* kErrCannotGoToPrevDir ; 
 int kErrInvalidDirParam ; 
 void* kErrMKDFailed ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 int kNoErr ; 
 int const kRecursiveNo ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 

int
FTPMkdir2(const FTPCIPtr cip, const char *const newDir, const int recurse, const char *const curDir)
{
	int result, result2;
	char *cp, *newTreeStart, *cp2;
	char dir[512];
	char dir2[512];
	char c;

	if (cip == NULL)
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);

	if ((newDir == NULL) || (newDir[0] == '\0')) {
		cip->errNo = kErrInvalidDirParam;
		return (kErrInvalidDirParam);
	}

	/* Preserve old working directory. */
	if ((curDir == NULL) || (curDir[0] == '\0')) {
		/* This hack is nice so you can eliminate an
		 * unnecessary "PWD" command on the server,
		 * since if you already knew what directory
		 * you're in.  We want to minimize the number
		 * of client-server exchanges when feasible.
		 */
		(void) FTPGetCWD(cip, cip->buf, cip->bufSize);
	}

	result = FTPChdir(cip, newDir);
	if (result == kNoErr) {
		/* Directory already exists -- but we
		 * must now change back to where we were.
		 */
		result2 = FTPChdir(cip, ((curDir == NULL) || (curDir[0] == '\0')) ? cip->buf : curDir);
		if (result2 < 0) {
			result = kErrCannotGoToPrevDir;
			cip->errNo = kErrCannotGoToPrevDir;
			return (result);
		}

		/* Don't need to create it. */
		return (kNoErr);
	}

	if (recurse == kRecursiveNo) {
		result = FTPCmd(cip, "MKD %s", newDir);
		if (result > 0) {
			if (result != 2) {
				Error(cip, kDontPerror, "MKD %s failed; [%s]\n", newDir, cip->lastFTPCmdResultStr);
				result = kErrMKDFailed;
				cip->errNo = kErrMKDFailed;
				return (result);
			} else {
				result = kNoErr;
			}
		}
	} else {
		(void) STRNCPY(dir, newDir);

		/* Strip trailing slashes. */
		cp = dir + strlen(dir) - 1;
		for (;;) {
			if (cp <= dir) {
				if ((newDir == NULL) || (newDir[0] == '\0')) {
					cip->errNo = kErrInvalidDirParam;
					result = kErrInvalidDirParam;
					return (result);
				}
			}
			if ((*cp != '/') && (*cp != '\\')) {
				cp[1] = '\0';
				break;
			}
			--cp;
		}
		(void) STRNCPY(dir2, dir);

		if ((strrchr(dir, '/') == dir) || (strrchr(dir, '\\') == dir)) {
			/* Special case "mkdir /subdir" */
			result = FTPCmd(cip, "MKD %s", dir);
			if (result < 0) {
				return (result);
			}
			if (result != 2) {
				Error(cip, kDontPerror, "MKD %s failed; [%s]\n", dir, cip->lastFTPCmdResultStr);
				result = kErrMKDFailed;
				cip->errNo = kErrMKDFailed;
				return (result);
			}
			/* Haven't chdir'ed, don't need to goto goback. */
			return (kNoErr);
		}

		for (;;) {
			cp = strrchr(dir, '/');
			if (cp == NULL)
				cp = strrchr(dir, '\\');
			if (cp == NULL) {
				cp = dir + strlen(dir) - 1;
				if (dir[0] == '\0') {
					result = kErrMKDFailed;
					cip->errNo = kErrMKDFailed;
					return (result);
				}
				/* Note: below we will refer to cp + 1
				 * which is why we set cp to point to
				 * the byte before the array begins!
				 */
				cp = dir - 1;
				break;
			}
			if (cp == dir) {
				result = kErrMKDFailed;
				cip->errNo = kErrMKDFailed;
				return (result);
			}
			*cp = '\0';
			result = FTPChdir(cip, dir);
			if (result == 0) {
				break;	/* Found a valid parent dir. */
				/* from this point, we need to preserve old dir. */
			}
		}

		newTreeStart = dir2 + ((cp + 1) - dir);
		for (cp = newTreeStart; ; ) {
			cp2 = cp;
			cp = strchr(cp2, '/');
			c = '/';
			if (cp == NULL)
				cp = strchr(cp2, '\\');
			if (cp != NULL) {
				c = *cp;
				*cp = '\0';
				if (cp[1] == '\0') {
					/* Done, if they did "mkdir /tmp/dir/" */
					break;
				}
			}
			result = FTPCmd(cip, "MKD %s", newTreeStart);
			if (result < 0) {
				return (result);
			}
			if (result != 2) {
				Error(cip, kDontPerror, "Cwd=%s; MKD %s failed; [%s]\n", cip->buf, newTreeStart, cip->lastFTPCmdResultStr);
				result = kErrMKDFailed;
				cip->errNo = kErrMKDFailed;
				goto goback;
			}
			if (cp == NULL)
				break;	/* No more to make, done. */
			*cp++ = c;
		}
		result = kNoErr;

goback:
		result2 = FTPChdir(cip, ((curDir == NULL) || (curDir[0] == '\0')) ? cip->buf : curDir);
		if ((result == 0) && (result2 < 0)) {
			result = kErrCannotGoToPrevDir;
			cip->errNo = kErrCannotGoToPrevDir;
		}
	}
	return (result);
}