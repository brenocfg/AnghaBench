#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ nsec_t ;
struct TYPE_6__ {scalar_t__ cpu_usage_last; scalar_t__ cpu_usage_base; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ NSEC_INFINITY ; 
 int /*<<< orphan*/  UNIT_CGROUP_BOOL (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  cpu_accounting ; 
 int unit_get_cpu_usage_raw (TYPE_1__*,scalar_t__*) ; 

int unit_get_cpu_usage(Unit *u, nsec_t *ret) {
        nsec_t ns;
        int r;

        assert(u);

        /* Retrieve the current CPU usage counter. This will subtract the CPU counter taken when the unit was
         * started. If the cgroup has been removed already, returns the last cached value. To cache the value, simply
         * call this function with a NULL return value. */

        if (!UNIT_CGROUP_BOOL(u, cpu_accounting))
                return -ENODATA;

        r = unit_get_cpu_usage_raw(u, &ns);
        if (r == -ENODATA && u->cpu_usage_last != NSEC_INFINITY) {
                /* If we can't get the CPU usage anymore (because the cgroup was already removed, for example), use our
                 * cached value. */

                if (ret)
                        *ret = u->cpu_usage_last;
                return 0;
        }
        if (r < 0)
                return r;

        if (ns > u->cpu_usage_base)
                ns -= u->cpu_usage_base;
        else
                ns = 0;

        u->cpu_usage_last = ns;
        if (ret)
                *ret = ns;

        return 0;
}