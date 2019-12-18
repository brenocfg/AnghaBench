#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {char const* magic; int errNo; } ;
struct TYPE_15__ {TYPE_1__* last; TYPE_1__* first; } ;
struct TYPE_14__ {int /*<<< orphan*/  line; struct TYPE_14__* next; } ;
typedef  TYPE_1__* LinePtr ;
typedef  TYPE_2__* LineListPtr ;
typedef  TYPE_3__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  AddLine (TYPE_2__*,char const*) ; 
 int FTPListToMemory2 (TYPE_3__*,char const*,TYPE_2__*,char const*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ GLOBCHARSINSTR (char const*) ; 
 int /*<<< orphan*/  InitLineList (TYPE_2__*) ; 
 int /*<<< orphan*/  PrintF (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoteGlobCollapse (char const*,TYPE_2__*) ; 
 int /*<<< orphan*/  RemoveLine (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ glberr (char*) ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 int kErrGlobFailed ; 
 int kErrGlobNoMatch ; 
 char* kLibraryMagic ; 
 int kNoErr ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int
FTPRemoteGlob(FTPCIPtr cip, LineListPtr fileList, const char *pattern, int doGlob)
{
	char *cp;
	const char *lsflags;
	LinePtr lp;
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

	/* Note that we do attempt to use glob characters even if the remote
	 * host isn't UNIX.  Most non-UNIX remote FTP servers look for UNIX
	 * style wildcards.
	 */
	if ((doGlob == 1) && (GLOBCHARSINSTR(pattern))) {
		/* Use NLST, which lists files one per line. */
		lsflags = "";

		/* Optimize for "NLST *" case which is same as "NLST". */
		if (strcmp(pattern, "*") == 0) {
			pattern = "";
		} else if (strcmp(pattern, "**") == 0) {
			/* Hack; Lets you try "NLST -a" if you're daring. */
			pattern = "";
			lsflags = "-a";
		}

		if ((result = FTPListToMemory2(cip, pattern, fileList, lsflags, 0, (int *) 0)) < 0) {
			if (*lsflags == '\0')
				return (result);
			/* Try again, without "-a" */
			lsflags = "";
			if ((result = FTPListToMemory2(cip, pattern, fileList, lsflags, 0, (int *) 0)) < 0) {
				return (result);
			}
		}
		if (fileList->first == NULL) {
			cip->errNo = kErrGlobNoMatch;
			return (kErrGlobNoMatch);
		}
		if (fileList->first == fileList->last) {
#define glberr(a) (ISTRNEQ(cp, a, strlen(a)))
			/* If we have only one item in the list, see if it really was
			 * an error message we would recognize.
			 */
			cp = strchr(fileList->first->line, ':');
			if (cp != NULL) {
				if (glberr(": No such file or directory")) {
					(void) RemoveLine(fileList, fileList->first);
					cip->errNo = kErrGlobFailed;
					return (kErrGlobFailed);
				} else if (glberr(": No match")) {
					cip->errNo = kErrGlobNoMatch;
					return (kErrGlobNoMatch);
				}
			}
		}
		RemoteGlobCollapse(pattern, fileList);
		for (lp=fileList->first; lp != NULL; lp = lp->next)
			PrintF(cip, "  Rglob [%s]\n", lp->line);
	} else {
		/* Or, if there were no globbing characters in 'pattern', then the
		 * pattern is really just a filename.  So for this case the
		 * file list is really just a single file.
		 */
		fileList->first = fileList->last = NULL;
		(void) AddLine(fileList, pattern);
	}
	return (kNoErr);
}