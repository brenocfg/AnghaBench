#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* noglobargv; } ;
typedef  int /*<<< orphan*/  CommandPtr ;
typedef  TYPE_1__* ArgvInfoPtr ;

/* Variables and functions */
 int /*<<< orphan*/  ARGSUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTPPerror (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char const*) ; 
 int FTPRmdir (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlushLsCache () ; 
 int Getopt (int const,char const** const,char*) ; 
 int /*<<< orphan*/  GetoptReset () ; 
 int /*<<< orphan*/  PrintCmdUsage (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gConn ; 
 int gOptInd ; 
 int /*<<< orphan*/  gUnusedArg ; 
 int /*<<< orphan*/  kErrRMDFailed ; 
 int /*<<< orphan*/  kGlobNo ; 
 int /*<<< orphan*/  kGlobYes ; 
 int kRecursiveNo ; 
 int kRecursiveYes ; 

void
RmdirCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
	int result;
	int i, c;
	int recursive = kRecursiveNo;

	ARGSUSED(gUnusedArg);
	GetoptReset();
	while ((c = Getopt(argc, argv, "rf")) > 0) switch(c) {
		case 'r':
			recursive = kRecursiveYes;
			break;
		case 'f':
			/* ignore */
			break;
		default:
			PrintCmdUsage(cmdp);
			return;
	}
	for (i=gOptInd; i<argc; i++) {
		result = FTPRmdir(&gConn, argv[i], recursive, (aip->noglobargv[i] != 0) ? kGlobNo: kGlobYes);
		if (result < 0)
			FTPPerror(&gConn, result, kErrRMDFailed, "rmdir", argv[i]);
	}

	/* Really should just flush only the modified directories... */
	FlushLsCache();
}