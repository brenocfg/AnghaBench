#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  savedcwd ;
typedef  int /*<<< orphan*/  curcwd ;
struct TYPE_11__ {int errNo; } ;
typedef  int (* FTPFtwProc ) (TYPE_1__* const,char*,int /*<<< orphan*/ ) ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int FTPChdir (TYPE_1__* const,char const* const) ; 
 int FTPFtwL2 (TYPE_1__* const,char*,char*,int,int (*) (TYPE_1__* const,char*,int /*<<< orphan*/ ),int) ; 
 int FTPGetCWD (TYPE_1__* const,char*,int) ; 
 int FTPIsDir (TYPE_1__* const,char const* const) ; 
 void* kErrCannotGoToPrevDir ; 
 int kErrNotADirectory ; 
 int /*<<< orphan*/  kFtwDir ; 
 int kNoErr ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/ * strrchr (char*,char) ; 
 int stub1 (TYPE_1__* const,char*,int /*<<< orphan*/ ) ; 

int
FTPFtw(const FTPCIPtr cip, const char *const dir, FTPFtwProc proc, int maxdepth)
{
	int result, result2;
	char *cp;
	char savedcwd[1024];
	char curcwd[2048];

	result = FTPIsDir(cip, dir);
	if (result < 0) {
		/* error */
		return result;
	} else if (result == 0) {
		result = cip->errNo = kErrNotADirectory;
		return (result);
	}

	/* Preserve old working directory. */
	(void) FTPGetCWD(cip, savedcwd, sizeof(savedcwd));

	result = FTPChdir(cip, dir);
	if (result != kNoErr) {
		return (result);
	}

	/* Get full working directory we just changed to. */
	result = FTPGetCWD(cip, curcwd, sizeof(curcwd) - 3);
	if (result != kNoErr) {
		if (FTPChdir(cip, savedcwd) != kNoErr) {
			result = kErrCannotGoToPrevDir;
			cip->errNo = kErrCannotGoToPrevDir;
		}
		return (result);
	}

	result2 = (*proc)(cip, curcwd, kFtwDir);
	if (result2 == kNoErr) {
		cp = curcwd + strlen(curcwd);

		if ((strchr(curcwd, '/') == NULL) && (strrchr(curcwd, '\\') != NULL))
			*cp++ = '\\';
		else
			*cp++ = '/';
		*cp = '\0';
		result = FTPFtwL2(cip, curcwd, cp, sizeof(curcwd), proc, maxdepth - 1);
	}


	if (FTPChdir(cip, savedcwd) != kNoErr) {
		/* Could not cd back to the original user directory -- bad. */
		result = kErrCannotGoToPrevDir;
		cip->errNo = kErrCannotGoToPrevDir;
		return (result);
	}

	if ((result2 != kNoErr) && (result == kNoErr))
		result = result2;

	return (result);
}