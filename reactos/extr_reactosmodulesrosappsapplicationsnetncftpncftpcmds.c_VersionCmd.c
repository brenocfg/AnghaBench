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
typedef  int /*<<< orphan*/  CommandPtr ;
typedef  int /*<<< orphan*/  ArgvInfoPtr ;

/* Variables and functions */
 int /*<<< orphan*/  ARGSUSED (int /*<<< orphan*/ ) ; 
 char* gLibNcFTPVersion ; 
 char* gOS ; 
 int /*<<< orphan*/  gUnusedArg ; 
 char* gVersion ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
VersionCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
	ARGSUSED(gUnusedArg);
	(void) printf("Version:          %s\n", gVersion + 5);
	(void) printf("Author:           Mike Gleason (ncftp@ncftp.com)\n");
#ifndef BETA
	(void) printf("Archived at:      ftp://ftp.ncftp.com/ncftp/\n");
#endif
	(void) printf("Library Version:  %s\n", gLibNcFTPVersion + 5);
#ifdef __DATE__
	(void) printf("Compile Date:     %s\n", __DATE__);
#endif
	if (gOS[0] != '\0')
		(void) printf("Platform:         %s\n", gOS);
}