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
struct TYPE_5__ {char** argv; int flags; scalar_t__ pid; scalar_t__ start_time; scalar_t__ retry_num; } ;
typedef  TYPE_1__ sentinelScriptJob ;
typedef  scalar_t__ mstime_t ;
struct TYPE_6__ {TYPE_1__* value; } ;
typedef  TYPE_2__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_7__ {int /*<<< orphan*/  scripts_queue; } ;

/* Variables and functions */
 int SENTINEL_SCRIPT_RUNNING ; 
 int /*<<< orphan*/  addReplyArrayLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  addReplyBulkCString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  addReplyBulkLongLong (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  addReplyMapLen (int /*<<< orphan*/ *,int) ; 
 int listLength (int /*<<< orphan*/ ) ; 
 TYPE_2__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mstime () ; 
 TYPE_3__ sentinel ; 

void sentinelPendingScriptsCommand(client *c) {
    listNode *ln;
    listIter li;

    addReplyArrayLen(c,listLength(sentinel.scripts_queue));
    listRewind(sentinel.scripts_queue,&li);
    while ((ln = listNext(&li)) != NULL) {
        sentinelScriptJob *sj = ln->value;
        int j = 0;

        addReplyMapLen(c,5);

        addReplyBulkCString(c,"argv");
        while (sj->argv[j]) j++;
        addReplyArrayLen(c,j);
        j = 0;
        while (sj->argv[j]) addReplyBulkCString(c,sj->argv[j++]);

        addReplyBulkCString(c,"flags");
        addReplyBulkCString(c,
            (sj->flags & SENTINEL_SCRIPT_RUNNING) ? "running" : "scheduled");

        addReplyBulkCString(c,"pid");
        addReplyBulkLongLong(c,sj->pid);

        if (sj->flags & SENTINEL_SCRIPT_RUNNING) {
            addReplyBulkCString(c,"run-time");
            addReplyBulkLongLong(c,mstime() - sj->start_time);
        } else {
            mstime_t delay = sj->start_time ? (sj->start_time-mstime()) : 0;
            if (delay < 0) delay = 0;
            addReplyBulkCString(c,"run-delay");
            addReplyBulkLongLong(c,delay);
        }

        addReplyBulkCString(c,"retry-num");
        addReplyBulkLongLong(c,sj->retry_num);
    }
}