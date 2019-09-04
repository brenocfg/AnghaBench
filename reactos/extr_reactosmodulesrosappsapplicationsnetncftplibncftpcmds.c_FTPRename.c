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
 int FTPCmd (TYPE_1__* const,char*,char const* const) ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 void* kErrRenameFailed ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 int kNoErr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
FTPRename(const FTPCIPtr cip, const char *const oldname, const char *const newname)
{
	int result;

	if (cip == NULL)
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);
	if ((oldname == NULL) || (oldname[0] == '\0'))
		return (kErrBadParameter);
	if ((newname == NULL) || (oldname[0] == '\0'))
		return (kErrBadParameter);


	result = FTPCmd(cip, "RNFR %s", oldname);
	if (result < 0)
		return (result);
	if (result != 3) {
		cip->errNo = kErrRenameFailed;
		return (cip->errNo);
	}

	result = FTPCmd(cip, "RNTO %s", newname);
	if (result < 0)
		return (result);
	if (result != 2) {
		cip->errNo = kErrRenameFailed;
		return (cip->errNo);
	}
	return (kNoErr);
}