#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int errNo; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int FTPFileType (TYPE_1__* const,char const* const,int*) ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 int kErrFileExistsButCannotDetermineType ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 int kNoErr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
FTPIsRegularFile(const FTPCIPtr cip, const char *const file)
{
	int result, ftype;

	if (cip == NULL)
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);

	if ((file == NULL) || (file[0] == '\0')) {
		cip->errNo = kErrBadParameter;
		return (kErrBadParameter);
	}

	result = FTPFileType(cip, file, &ftype);
	if ((result == kNoErr) || (result == kErrFileExistsButCannotDetermineType)) {
		result = 1;
		if (ftype == 'd')
			result = 0;
	}
	return (result);
}