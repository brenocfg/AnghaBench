#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* first; } ;
struct TYPE_6__ {char* line; struct TYPE_6__* next; } ;
struct TYPE_5__ {int printMode; int codeType; TYPE_3__ msg; } ;
typedef  TYPE_1__* ResponsePtr ;
typedef  TYPE_2__* LinePtr ;
typedef  TYPE_3__* LineListPtr ;
typedef  int /*<<< orphan*/ * FTPCIPtr ;

/* Variables and functions */
 scalar_t__ ISTRNCMP (char*,char*,int) ; 
 int /*<<< orphan*/  gUnusedArg ; 
 int kResponseNoPrint ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
NcFTPCdResponseProc(const FTPCIPtr cipUNUSED, ResponsePtr rp)
{
	LinePtr lp;
	LineListPtr llp;

	gUnusedArg = (cipUNUSED != NULL);
	if ((rp->printMode & kResponseNoPrint) != 0)
		return;
	llp = &rp->msg;
	for (lp = llp->first; lp != NULL; lp = lp->next) {
		if ((lp == llp->first) && (rp->codeType == 2)) {
			if (ISTRNCMP(lp->line, "CWD command", 11) == 0)
				continue;
			if (lp->line[0] == '"')
				continue;	/* "/pub/foo" is... */
		}
		(void) printf("%s\n", lp->line);
	}
}