#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  jobs; } ;
typedef  TYPE_1__ BusWaitForJobs ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int set_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int set_put_strdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  string_hash_ops ; 

int bus_wait_for_jobs_add(BusWaitForJobs *d, const char *path) {
        int r;

        assert(d);

        r = set_ensure_allocated(&d->jobs, &string_hash_ops);
        if (r < 0)
                return r;

        return set_put_strdup(d->jobs, path);
}