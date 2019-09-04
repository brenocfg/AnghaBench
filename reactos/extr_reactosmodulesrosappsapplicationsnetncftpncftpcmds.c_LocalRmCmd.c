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
 int /*<<< orphan*/  Sys (int const,char const** const,int /*<<< orphan*/  const,char*,int) ; 
 int /*<<< orphan*/  gUnusedArg ; 

void
LocalRmCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
#if defined(WIN32) || defined(_WINDOWS)
	int i;
	int result;
	LineList ll;
	LinePtr lp;

	ARGSUSED(gUnusedArg);
	for (i=1; i<argc; i++) {
		InitLineList(&ll);
		result = FTPLocalGlob(&gConn, &ll, argv[i], (aip->noglobargv[i] != 0) ? kGlobNo: kGlobYes);
		if (result < 0) {
			FTPPerror(&gConn, result, kErrGlobFailed, "local glob", argv[i]);
		} else {
			for (lp = ll.first; lp != NULL; lp = lp->next) {
				if (lp->line != NULL) {
					if (remove(lp->line) < 0)
						perror(lp->line);
				}
			}
		}
		DisposeLineListContents(&ll);
	}
#else
	ARGSUSED(gUnusedArg);
	Sys(argc, argv, aip, "/bin/rm", 1);
#endif
}