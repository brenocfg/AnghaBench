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
 int FTPChmod (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTPPerror (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  FlushLsCache () ; 
 int /*<<< orphan*/  gConn ; 
 int /*<<< orphan*/  gUnusedArg ; 
 int /*<<< orphan*/  kErrChmodFailed ; 
 int /*<<< orphan*/  kGlobNo ; 
 int /*<<< orphan*/  kGlobYes ; 

void
ChmodCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
	int i, result;

	ARGSUSED(gUnusedArg);
	for (i=2; i<argc; i++) {
		result = FTPChmod(
				&gConn, argv[i], argv[1],
				(aip->noglobargv[i] != 0) ? kGlobNo: kGlobYes
			);
		if (result < 0) {
			FTPPerror(&gConn, result, kErrChmodFailed, "chmod", argv[i]);
			/* but continue */
		}
	}

	/* Really should just flush only the modified directories... */
	FlushLsCache();
}