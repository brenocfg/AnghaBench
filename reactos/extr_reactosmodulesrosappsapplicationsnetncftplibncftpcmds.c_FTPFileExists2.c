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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  longest_int ;
struct TYPE_8__ {int errNo; } ;
typedef  int /*<<< orphan*/  MLstItem ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int FTPFileExistsNlst (TYPE_1__* const,char const* const) ; 
 int FTPFileExistsStat (TYPE_1__* const,char const* const) ; 
 int FTPFileModificationTime (TYPE_1__* const,char const* const,int /*<<< orphan*/ *) ; 
 int FTPFileSize (TYPE_1__* const,char const* const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int FTPMListOneFile (TYPE_1__* const,char const* const,int /*<<< orphan*/ *) ; 
 int kErrCantTellIfFileExists ; 
 int kErrMDTMFailed ; 
 int kErrMLSTFailed ; 
 int kErrNLSTFailed ; 
 int kErrNoSuchFileOrDirectory ; 
 int kErrSTATFailed ; 
 int kNoErr ; 
 int /*<<< orphan*/  kTypeBinary ; 

int
FTPFileExists2(const FTPCIPtr cip, const char *const file, const int tryMDTM, const int trySIZE, const int tryMLST, const int trySTAT, const int tryNLST)
{
	int result;
	time_t mdtm;
	longest_int size;
	MLstItem mlsInfo;

	if (tryMDTM != 0) {
		result = FTPFileModificationTime(cip, file, &mdtm);
		if (result == kNoErr)
			return (kNoErr);
		if (result == kErrMDTMFailed) {
			cip->errNo = kErrNoSuchFileOrDirectory;
			return (kErrNoSuchFileOrDirectory);
		}
		/* else keep going */
	}

	if (trySIZE != 0) {
		result = FTPFileSize(cip, file, &size, kTypeBinary);
		if (result == kNoErr)
			return (kNoErr);
		/* SIZE could fail if the server does
		 * not support it for directories.
		 *
		 * if (result == kErrSIZEFailed)
		 *	return (kErrNoSuchFileOrDirectory);
		 */
		/* else keep going */
	}


	if (tryMLST != 0) {
		result = FTPMListOneFile(cip, file, &mlsInfo);
		if (result == kNoErr)
			return (kNoErr);
		if (result == kErrMLSTFailed) {
			cip->errNo = kErrNoSuchFileOrDirectory;
			return (kErrNoSuchFileOrDirectory);
		}
		/* else keep going */
	}

	if (trySTAT != 0) {
		result = FTPFileExistsStat(cip, file);
		if (result == kNoErr)
			return (kNoErr);
		if (result == kErrSTATFailed) {
			cip->errNo = kErrNoSuchFileOrDirectory;
			return (kErrNoSuchFileOrDirectory);
		}
		/* else keep going */
	}

	if (tryNLST != 0) {
		result = FTPFileExistsNlst(cip, file);
		if (result == kNoErr)
			return (kNoErr);
		if (result == kErrNLSTFailed) {
			cip->errNo = kErrNoSuchFileOrDirectory;
			return (kErrNoSuchFileOrDirectory);
		}
		/* else keep going */
	}

	cip->errNo = kErrCantTellIfFileExists;
	return (kErrCantTellIfFileExists);
}