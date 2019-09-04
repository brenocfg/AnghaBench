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
 int FTPGetOneFile2 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTPPerror (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  gConn ; 
 int /*<<< orphan*/  gUnusedArg ; 
 int /*<<< orphan*/  kAppendNo ; 
 int /*<<< orphan*/  kErrCouldNotStartDataTransfer ; 
 int /*<<< orphan*/  kResumeNo ; 
 int /*<<< orphan*/  kTypeAscii ; 

void
CatCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
	int result;
	int i;

	ARGSUSED(gUnusedArg);
	for (i=1; i<argc; i++) {
		result = FTPGetOneFile2(&gConn, argv[i], NULL, kTypeAscii, STDOUT_FILENO, kResumeNo, kAppendNo);
		FTPPerror(&gConn, result, kErrCouldNotStartDataTransfer, "cat", argv[i]);
	}
}