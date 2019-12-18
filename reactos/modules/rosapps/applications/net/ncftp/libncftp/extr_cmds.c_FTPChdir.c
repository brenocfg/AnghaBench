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
struct TYPE_4__ {char const* const magic; void* errNo; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int FTPCmd (TYPE_1__* const,char*,...) ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 void* kErrCWDFailed ; 
 void* kErrInvalidDirParam ; 
 char* kLibraryMagic ; 
 int kNoErr ; 
 scalar_t__ strcmp (char const* const,char*) ; 

int
FTPChdir(const FTPCIPtr cip, const char *const cdCwd)
{
	int result;

	if (cip == NULL)
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);

	if (cdCwd == NULL) {
		result = kErrInvalidDirParam;
		cip->errNo = kErrInvalidDirParam;
	} else {
		if (cdCwd[0] == '\0')	/* But allow FTPChdir(cip, ".") to go through. */
			result = 2;
		else if (strcmp(cdCwd, "..") == 0)
			result = FTPCmd(cip, "CDUP");
		else
			result = FTPCmd(cip, "CWD %s", cdCwd);
		if (result >= 0) {
			if (result == 2) {
				result = kNoErr;
			} else {
				result = kErrCWDFailed;
				cip->errNo = kErrCWDFailed;
			}
		}
	}
	return (result);
}