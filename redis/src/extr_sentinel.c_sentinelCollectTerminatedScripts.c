#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ retry_num; long* argv; scalar_t__ start_time; scalar_t__ pid; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ sentinelScriptJob ;
typedef  scalar_t__ pid_t ;
struct TYPE_8__ {TYPE_1__* value; } ;
typedef  TYPE_2__ listNode ;
struct TYPE_9__ {int /*<<< orphan*/  running_scripts; int /*<<< orphan*/  scripts_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_DEBUG ; 
 int /*<<< orphan*/  LL_WARNING ; 
 scalar_t__ SENTINEL_SCRIPT_MAX_RETRY ; 
 int /*<<< orphan*/  SENTINEL_SCRIPT_RUNNING ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WNOHANG ; 
 int WTERMSIG (int) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ mstime () ; 
 TYPE_5__ sentinel ; 
 int /*<<< orphan*/  sentinelEvent (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,long,int,int) ; 
 TYPE_2__* sentinelGetScriptListNodeByPid (scalar_t__) ; 
 int /*<<< orphan*/  sentinelReleaseScriptJob (TYPE_1__*) ; 
 scalar_t__ sentinelScriptRetryDelay (scalar_t__) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,long) ; 
 scalar_t__ wait3 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void sentinelCollectTerminatedScripts(void) {
    int statloc;
    pid_t pid;

    while ((pid = wait3(&statloc,WNOHANG,NULL)) > 0) {
        int exitcode = WEXITSTATUS(statloc);
        int bysignal = 0;
        listNode *ln;
        sentinelScriptJob *sj;

        if (WIFSIGNALED(statloc)) bysignal = WTERMSIG(statloc);
        sentinelEvent(LL_DEBUG,"-script-child",NULL,"%ld %d %d",
            (long)pid, exitcode, bysignal);

        ln = sentinelGetScriptListNodeByPid(pid);
        if (ln == NULL) {
            serverLog(LL_WARNING,"wait3() returned a pid (%ld) we can't find in our scripts execution queue!", (long)pid);
            continue;
        }
        sj = ln->value;

        /* If the script was terminated by a signal or returns an
         * exit code of "1" (that means: please retry), we reschedule it
         * if the max number of retries is not already reached. */
        if ((bysignal || exitcode == 1) &&
            sj->retry_num != SENTINEL_SCRIPT_MAX_RETRY)
        {
            sj->flags &= ~SENTINEL_SCRIPT_RUNNING;
            sj->pid = 0;
            sj->start_time = mstime() +
                             sentinelScriptRetryDelay(sj->retry_num);
        } else {
            /* Otherwise let's remove the script, but log the event if the
             * execution did not terminated in the best of the ways. */
            if (bysignal || exitcode != 0) {
                sentinelEvent(LL_WARNING,"-script-error",NULL,
                              "%s %d %d", sj->argv[0], bysignal, exitcode);
            }
            listDelNode(sentinel.scripts_queue,ln);
            sentinelReleaseScriptJob(sj);
            sentinel.running_scripts--;
        }
    }
}