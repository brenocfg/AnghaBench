#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long pid_t ;
struct TYPE_4__ {scalar_t__ value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_5__ {int /*<<< orphan*/  children; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  kill (unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_3__ ldb ; 
 int /*<<< orphan*/  listCreate () ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,long) ; 

void ldbKillForkedSessions(void) {
    listIter li;
    listNode *ln;

    listRewind(ldb.children,&li);
    while((ln = listNext(&li))) {
        pid_t pid = (unsigned long) ln->value;
        serverLog(LL_WARNING,"Killing debugging session %ld",(long)pid);
        kill(pid,SIGKILL);
    }
    listRelease(ldb.children);
    ldb.children = listCreate();
}