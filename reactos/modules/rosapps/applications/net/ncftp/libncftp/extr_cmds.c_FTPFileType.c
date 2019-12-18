#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int errNo; char const* const buf; int /*<<< orphan*/  bufSize; int /*<<< orphan*/  magic; } ;
struct TYPE_9__ {int ftype; } ;
typedef  TYPE_1__ MLstItem ;
typedef  TYPE_2__* FTPCIPtr ;

/* Variables and functions */
 int FTPChdir (TYPE_2__* const,char const* const) ; 
 int FTPFileExists2 (TYPE_2__* const,char const* const,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  FTPGetCWD (TYPE_2__* const,char const* const,int /*<<< orphan*/ ) ; 
 int FTPMListOneFile (TYPE_2__* const,char const* const,TYPE_1__*) ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 int kErrFileExistsButCannotDetermineType ; 
 int kErrNoSuchFileOrDirectory ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 int kNoErr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
FTPFileType(const FTPCIPtr cip, const char *const file, int *const ftype)
{
	int result;
	MLstItem mlsInfo;

	if (cip == NULL)
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);

	if ((file == NULL) || (file[0] == '\0')) {
		cip->errNo = kErrBadParameter;
		return (kErrBadParameter);
	}

	if (ftype == NULL) {
		cip->errNo = kErrBadParameter;
		return (kErrBadParameter);
	}

	*ftype = 0;
	result = FTPMListOneFile(cip, file, &mlsInfo);
	if (result == kNoErr) {
		*ftype = mlsInfo.ftype;
		return (kNoErr);
	}

	/* Preserve old working directory. */
	(void) FTPGetCWD(cip, cip->buf, cip->bufSize);

	result = FTPChdir(cip, file);
	if (result == kNoErr) {
		*ftype = 'd';
		/* Yes it was a directory, now go back to
		 * where we were.
		 */
		(void) FTPChdir(cip, cip->buf);

		/* Note:  This improperly assumes that we
		 * will be able to chdir back, which is
		 * not guaranteed.
		 */
		return (kNoErr);
	}

	result = FTPFileExists2(cip, file, 1, 1, 0, 1, 1);
	if (result != kErrNoSuchFileOrDirectory)
		result = kErrFileExistsButCannotDetermineType;

	return (result);
}