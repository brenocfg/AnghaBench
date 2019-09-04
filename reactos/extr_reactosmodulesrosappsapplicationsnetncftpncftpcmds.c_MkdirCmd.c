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
 int FTPMkdir (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  FTPPerror (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  FlushLsCache () ; 
 int Getopt (int const,char const** const,char*) ; 
 int /*<<< orphan*/  GetoptReset () ; 
 int /*<<< orphan*/  PrintCmdUsage (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gConn ; 
 int gOptInd ; 
 int /*<<< orphan*/  gUnusedArg ; 
 int /*<<< orphan*/  kErrMKDFailed ; 
 int kRecursiveNo ; 
 int kRecursiveYes ; 

void
MkdirCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
	int i;
	int opt;
	int result;
	int recurseFlag = kRecursiveNo;

	ARGSUSED(gUnusedArg);
	GetoptReset();
	while ((opt = Getopt(argc, argv, "p")) >= 0) {
		if (opt == 'p') {
			/* Try creating intermediate directories if they
			 * don't exist.
			 *
			 * For example if only /pub/stuff existed, and you
			 * do a "mkdir -p /pub/stuff/a/b/c", the "a" and "b"
			 * directories would also be created.
			 */
			recurseFlag = kRecursiveYes;
		} else {
			PrintCmdUsage(cmdp);
			return;
		}
	}

	for (i=gOptInd; i<argc; i++) {
		result = FTPMkdir(&gConn, argv[i], recurseFlag);
		if (result < 0)
			FTPPerror(&gConn, result, kErrMKDFailed, "Could not mkdir", argv[i]);
	}

	/* Really should just flush only the modified directories... */
	FlushLsCache();
}