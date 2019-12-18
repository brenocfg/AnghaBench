#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* result; void* name; int /*<<< orphan*/  bus; int /*<<< orphan*/  jobs; } ;
typedef  TYPE_1__ BusWaitForJobs ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_process_wait (int /*<<< orphan*/ ) ; 
 int check_wait_response (TYPE_1__*,int,char const* const*) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*,void*,void*) ; 
 int log_error_errno (int,char*) ; 
 void* mfree (void*) ; 
 int /*<<< orphan*/  set_isempty (int /*<<< orphan*/ ) ; 

int bus_wait_for_jobs(BusWaitForJobs *d, bool quiet, const char* const* extra_args) {
        int r = 0;

        assert(d);

        while (!set_isempty(d->jobs)) {
                int q;

                q = bus_process_wait(d->bus);
                if (q < 0)
                        return log_error_errno(q, "Failed to wait for response: %m");

                if (d->name && d->result) {
                        q = check_wait_response(d, quiet, extra_args);
                        /* Return the first error as it is most likely to be
                         * meaningful. */
                        if (q < 0 && r == 0)
                                r = q;

                        log_debug_errno(q, "Got result %s/%m for job %s", d->result, d->name);
                }

                d->name = mfree(d->name);
                d->result = mfree(d->result);
        }

        return r;
}