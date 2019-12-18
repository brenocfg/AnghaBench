#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct moduleLoadQueueEntry {int /*<<< orphan*/  path; int /*<<< orphan*/  argc; scalar_t__ argv; } ;
struct TYPE_4__ {struct moduleLoadQueueEntry* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_5__ {int /*<<< orphan*/  loadmodule_queue; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ moduleLoad (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void moduleLoadFromQueue(void) {
    listIter li;
    listNode *ln;

    listRewind(server.loadmodule_queue,&li);
    while((ln = listNext(&li))) {
        struct moduleLoadQueueEntry *loadmod = ln->value;
        if (moduleLoad(loadmod->path,(void **)loadmod->argv,loadmod->argc)
            == C_ERR)
        {
            serverLog(LL_WARNING,
                "Can't load module from %s: server aborting",
                loadmod->path);
            exit(1);
        }
    }
}