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
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {scalar_t__* io_accounting_last; scalar_t__* io_accounting_base; } ;
typedef  TYPE_1__ Unit ;
typedef  size_t CGroupIOAccountingMetric ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  UNIT_CGROUP_BOOL (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int _CGROUP_IO_ACCOUNTING_METRIC_MAX ; 
 int /*<<< orphan*/  io_accounting ; 
 int unit_get_io_accounting_raw (TYPE_1__*,scalar_t__*) ; 

int unit_get_io_accounting(
                Unit *u,
                CGroupIOAccountingMetric metric,
                bool allow_cache,
                uint64_t *ret) {

        uint64_t raw[_CGROUP_IO_ACCOUNTING_METRIC_MAX];
        int r;

        /* Retrieve an IO account parameter. This will subtract the counter when the unit was started. */

        if (!UNIT_CGROUP_BOOL(u, io_accounting))
                return -ENODATA;

        if (allow_cache && u->io_accounting_last[metric] != UINT64_MAX)
                goto done;

        r = unit_get_io_accounting_raw(u, raw);
        if (r == -ENODATA && u->io_accounting_last[metric] != UINT64_MAX)
                goto done;
        if (r < 0)
                return r;

        for (CGroupIOAccountingMetric i = 0; i < _CGROUP_IO_ACCOUNTING_METRIC_MAX; i++) {
                /* Saturated subtraction */
                if (raw[i] > u->io_accounting_base[i])
                        u->io_accounting_last[i] = raw[i] - u->io_accounting_base[i];
                else
                        u->io_accounting_last[i] = 0;
        }

done:
        if (ret)
                *ret = u->io_accounting_last[metric];

        return 0;
}