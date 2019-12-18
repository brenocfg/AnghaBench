#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int in_run_queue; int /*<<< orphan*/  run_queue_idx; TYPE_1__* manager; struct TYPE_7__* installed; } ;
struct TYPE_6__ {int /*<<< orphan*/  run_queue; int /*<<< orphan*/  run_queue_event_source; } ;
typedef  TYPE_2__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 scalar_t__ prioq_isempty (int /*<<< orphan*/ ) ; 
 int prioq_put (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int sd_event_source_set_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void job_add_to_run_queue(Job *j) {
        int r;

        assert(j);
        assert(j->installed);

        if (j->in_run_queue)
                return;

        if (prioq_isempty(j->manager->run_queue)) {
                r = sd_event_source_set_enabled(j->manager->run_queue_event_source, SD_EVENT_ONESHOT);
                if (r < 0)
                        log_warning_errno(r, "Failed to enable job run queue event source, ignoring: %m");
        }

        r = prioq_put(j->manager->run_queue, j, &j->run_queue_idx);
        if (r < 0)
                log_warning_errno(r, "Failed put job in run queue, ignoring: %m");
        else
                j->in_run_queue = true;
}