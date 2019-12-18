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
typedef  scalar_t__ JobType ;

/* Variables and functions */
 scalar_t__ JOB_RELOAD ; 

__attribute__((used)) static bool job_type_allows_late_merge(JobType t) {
        /* Tells whether it is OK to merge a job of type 't' with an already
         * running job.
         * Reloads cannot be merged this way. Think of the sequence:
         * 1. Reload of a daemon is in progress; the daemon has already loaded
         *    its config file, but hasn't completed the reload operation yet.
         * 2. Edit foo's config file.
         * 3. Trigger another reload to have the daemon use the new config.
         * Should the second reload job be merged into the first one, the daemon
         * would not know about the new config.
         * JOB_RESTART jobs on the other hand can be merged, because they get
         * patched into JOB_START after stopping the unit. So if we see a
         * JOB_RESTART running, it means the unit hasn't stopped yet and at
         * this time the merge is still allowed. */
        return t != JOB_RELOAD;
}