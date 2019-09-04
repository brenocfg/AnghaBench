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
 int /*<<< orphan*/  FTPPerror (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char const*) ; 
 int FTPSymlink (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  FlushLsCache () ; 
 int /*<<< orphan*/  gConn ; 
 int /*<<< orphan*/  gUnusedArg ; 
 int /*<<< orphan*/  kErrSYMLINKFailed ; 

void
SymlinkCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
	int result;

	ARGSUSED(gUnusedArg);
	result = FTPSymlink(&gConn, argv[1], argv[2]);
	if (result < 0)
		FTPPerror(&gConn, result, kErrSYMLINKFailed, "symlink", argv[1]);

	/* Really should just flush only the modified directories... */
	FlushLsCache();
}