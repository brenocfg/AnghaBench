#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__* noglobargv; } ;
struct TYPE_9__ {TYPE_1__* first; } ;
struct TYPE_8__ {char* line; struct TYPE_8__* next; } ;
typedef  TYPE_1__* LinePtr ;
typedef  TYPE_2__ LineList ;
typedef  int /*<<< orphan*/  CommandPtr ;
typedef  TYPE_3__* ArgvInfoPtr ;

/* Variables and functions */
 int /*<<< orphan*/  ARGSUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DisposeLineListContents (TYPE_2__*) ; 
 int /*<<< orphan*/  FTPPerror (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char const*) ; 
 int FTPRemoteGlob (int /*<<< orphan*/ *,TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitLineList (TYPE_2__*) ; 
 int /*<<< orphan*/  gConn ; 
 int /*<<< orphan*/  gUnusedArg ; 
 int /*<<< orphan*/  kErrGlobFailed ; 
 int /*<<< orphan*/  kGlobNo ; 
 int /*<<< orphan*/  kGlobYes ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
RGlobCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
	int i;
	int result;
	int np = 0;
	LineList ll;
	LinePtr lp;

	ARGSUSED(gUnusedArg);
	for (i=1; i<argc; i++) {
		InitLineList(&ll);
		result = FTPRemoteGlob(&gConn, &ll, argv[i], (aip->noglobargv[i] != 0) ? kGlobNo: kGlobYes);
		if (result < 0) {
			FTPPerror(&gConn, result, kErrGlobFailed, "remote glob", argv[i]);
		} else {
			for (lp = ll.first; lp != NULL; lp = lp->next) {
				if (lp->line != NULL) {
					if (np > 0)
						(void) printf(" ");
					(void) printf("%s", lp->line);
					np++;
				}
			}
		}
		DisposeLineListContents(&ll);
	}
	(void) printf("\n");
}