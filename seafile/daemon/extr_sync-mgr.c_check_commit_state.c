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
struct TYPE_5__ {int /*<<< orphan*/  commit_timer; TYPE_1__* mgr; } ;
struct TYPE_4__ {int /*<<< orphan*/  commit_job_running; } ;
typedef  TYPE_2__ SyncTask ;

/* Variables and functions */
 int /*<<< orphan*/  commit_repo (TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_timer_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
check_commit_state (void *data)
{
    SyncTask *task = data;

    if (!task->mgr->commit_job_running) {
        seaf_timer_free (&task->commit_timer);
        commit_repo (task);
        return 0;
    }

    return 1;
}