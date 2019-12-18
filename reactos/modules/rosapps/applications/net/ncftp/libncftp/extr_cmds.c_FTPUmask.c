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
struct TYPE_4__ {int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int FTPCmd (TYPE_1__* const,char*,char const* const) ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 int kErrUmaskFailed ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 int kNoErr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
FTPUmask(const FTPCIPtr cip, const char *const umsk)
{
	if (cip == NULL)
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);
	if ((umsk == NULL) || (umsk[0] == '\0'))
		return (kErrBadParameter);
	if (FTPCmd(cip, "SITE UMASK %s", umsk) == 2)
		return (kNoErr);
	return (kErrUmaskFailed);
}