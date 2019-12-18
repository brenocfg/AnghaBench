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
typedef  int /*<<< orphan*/  BusWaitForJobs ;

/* Variables and functions */
 int bus_wait_for_jobs (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int bus_wait_for_jobs_add (int /*<<< orphan*/ *,char const*) ; 
 int log_oom () ; 

int bus_wait_for_jobs_one(BusWaitForJobs *d, const char *path, bool quiet) {
        int r;

        r = bus_wait_for_jobs_add(d, path);
        if (r < 0)
                return log_oom();

        return bus_wait_for_jobs(d, quiet, NULL);
}