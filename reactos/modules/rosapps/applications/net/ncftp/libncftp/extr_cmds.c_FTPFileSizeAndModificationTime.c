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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  longest_int ;
struct TYPE_10__ {int /*<<< orphan*/  magic; } ;
struct TYPE_9__ {int /*<<< orphan*/  fsize; int /*<<< orphan*/  ftime; } ;
typedef  TYPE_1__ MLstItem ;
typedef  TYPE_2__* FTPCIPtr ;

/* Variables and functions */
 int FTPFileModificationTime (TYPE_2__* const,char const* const,int /*<<< orphan*/ * const) ; 
 int FTPFileSize (TYPE_2__* const,char const* const,int /*<<< orphan*/ * const,int const) ; 
 int FTPMListOneFile (TYPE_2__* const,char const* const,TYPE_1__*) ; 
 int FTPSetTransferType (TYPE_2__* const,int const) ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 int /*<<< orphan*/  kModTimeUnknown ; 
 int /*<<< orphan*/  kSizeUnknown ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
FTPFileSizeAndModificationTime(const FTPCIPtr cip, const char *const file, longest_int *const size, const int type, time_t *const mdtm)
{
	MLstItem mlsInfo;
	int result;

	if (cip == NULL)
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);

	if ((mdtm == NULL) || (size == NULL) || (file == NULL))
		return (kErrBadParameter);

	*mdtm = kModTimeUnknown;
	*size = kSizeUnknown;

	result = FTPSetTransferType(cip, type);
	if (result < 0)
		return (result);

	result = FTPMListOneFile(cip, file, &mlsInfo);
	if (result < 0) {
		/* Do it the regular way, where
		 * we do a SIZE and then a MDTM.
		 */
		result = FTPFileSize(cip, file, size, type);
		if (result < 0)
			return (result);
		result = FTPFileModificationTime(cip, file, mdtm);
		return (result);
	} else {
		*mdtm = mlsInfo.ftime;
		*size = mlsInfo.fsize;
	}

	return (result);
}