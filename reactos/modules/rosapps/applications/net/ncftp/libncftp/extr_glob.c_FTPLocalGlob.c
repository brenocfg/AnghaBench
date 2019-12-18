#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  string ;
typedef  int /*<<< orphan*/  pattern2 ;
struct TYPE_5__ {int /*<<< orphan*/  magic; } ;
typedef  int /*<<< orphan*/ * LineListPtr ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  AddLine (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExpandTilde (int /*<<< orphan*/ ,int) ; 
 scalar_t__ GLOBCHARSINSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitLineList (int /*<<< orphan*/ *) ; 
 int LazyUnixLocalGlob (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRNCPY (int /*<<< orphan*/ ,char const*) ; 
 int WinLocalGlob (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 int kNoErr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
FTPLocalGlob(FTPCIPtr cip, LineListPtr fileList, const char *pattern, int doGlob)
{
	string pattern2;
	int result;

	if (cip == NULL)
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);

	if (fileList == NULL)
		return (kErrBadParameter);
	InitLineList(fileList);

	if ((pattern == NULL) || (pattern[0] == '\0'))
		return (kErrBadParameter);

	(void) STRNCPY(pattern2, pattern);	/* Don't nuke the original. */

	/* Pre-process for ~'s. */
	ExpandTilde(pattern2, sizeof(pattern2));
	InitLineList(fileList);
	result = kNoErr;

	if ((doGlob == 1) && (GLOBCHARSINSTR(pattern2))) {
#if defined(WIN32) || defined(_WINDOWS)
		result = WinLocalGlob(cip, fileList, pattern2);
#else
		result = LazyUnixLocalGlob(cip, fileList, pattern2);
#endif
	} else {
		/* Or, if there were no globbing characters in 'pattern', then
		 * the pattern is really just a single pathname.
		 */
		(void) AddLine(fileList, pattern2);
	}

	return (result);
}