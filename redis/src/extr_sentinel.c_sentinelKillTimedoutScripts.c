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
struct TYPE_5__ {int flags; scalar_t__ start_time; scalar_t__ pid; int /*<<< orphan*/ * argv; } ;
typedef  TYPE_1__ sentinelScriptJob ;
typedef  scalar_t__ mstime_t ;
struct TYPE_6__ {TYPE_1__* value; } ;
typedef  TYPE_2__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_7__ {int /*<<< orphan*/  scripts_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WARNING ; 
 scalar_t__ SENTINEL_SCRIPT_MAX_RUNTIME ; 
 int SENTINEL_SCRIPT_RUNNING ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mstime () ; 
 TYPE_3__ sentinel ; 
 int /*<<< orphan*/  sentinelEvent (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,long) ; 

void sentinelKillTimedoutScripts(void) {
    listNode *ln;
    listIter li;
    mstime_t now = mstime();

    listRewind(sentinel.scripts_queue,&li);
    while ((ln = listNext(&li)) != NULL) {
        sentinelScriptJob *sj = ln->value;

        if (sj->flags & SENTINEL_SCRIPT_RUNNING &&
            (now - sj->start_time) > SENTINEL_SCRIPT_MAX_RUNTIME)
        {
            sentinelEvent(LL_WARNING,"-script-timeout",NULL,"%s %ld",
                sj->argv[0], (long)sj->pid);
            kill(sj->pid,SIGKILL);
        }
    }
}