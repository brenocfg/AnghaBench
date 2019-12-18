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
typedef  int /*<<< orphan*/  usec_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ JOBS_IN_PROGRESS_PERIOD_USEC ; 
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  manager_print_jobs_in_progress (int /*<<< orphan*/ *) ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 int sd_event_source_set_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sd_event_source_set_time (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int manager_dispatch_jobs_in_progress(sd_event_source *source, usec_t usec, void *userdata) {
        Manager *m = userdata;
        int r;
        uint64_t next;

        assert(m);
        assert(source);

        manager_print_jobs_in_progress(m);

        next = now(CLOCK_MONOTONIC) + JOBS_IN_PROGRESS_PERIOD_USEC;
        r = sd_event_source_set_time(source, next);
        if (r < 0)
                return r;

        return sd_event_source_set_enabled(source, SD_EVENT_ONESHOT);
}