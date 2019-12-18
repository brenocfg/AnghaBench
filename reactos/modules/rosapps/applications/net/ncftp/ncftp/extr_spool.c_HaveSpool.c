#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ncftpbatch ;

/* Variables and functions */
 int /*<<< orphan*/  BINDIR ; 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  OurInstallationPath (char*,int,char*) ; 
 int /*<<< orphan*/  STRNCAT (char*,char*) ; 
 int /*<<< orphan*/  STRNCPY (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X_OK ; 
 scalar_t__ _access (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int gHaveSpool ; 
 char* gOurInstallationPath ; 
 scalar_t__ geteuid () ; 
 scalar_t__ system (char*) ; 

int
HaveSpool(void)
{
#if defined(WIN32) || defined(_WINDOWS)
	char ncftpbatch[260];

	if (gHaveSpool < 0) {
		gHaveSpool = 0;
		if (gOurInstallationPath[0] != '\0') {
			OurInstallationPath(ncftpbatch, sizeof(ncftpbatch), "ncftpbatch.exe");
			gHaveSpool = (_access(ncftpbatch, F_OK) == 0) ? 1 : 0;
		}
	}
#elif defined(BINDIR)
	char ncftpbatch[256];

	if (gHaveSpool < 0) {
		STRNCPY(ncftpbatch, BINDIR);
		STRNCAT(ncftpbatch, "/");
		STRNCAT(ncftpbatch, "ncftpbatch");
		gHaveSpool = (access(ncftpbatch, X_OK) == 0) ? 1 : 0;
	}
#else	/* BINDIR */
	if (gHaveSpool < 0) {
		if (geteuid() == 0) {
			gHaveSpool = (access("/usr/bin/ncftpbatch", X_OK) == 0) ? 1 : 0;
		} else {
			gHaveSpool = (system("ncftpbatch -X") == 0) ? 1 : 0;
		}
	}
#endif /* BINDIR */

	return (gHaveSpool);
}