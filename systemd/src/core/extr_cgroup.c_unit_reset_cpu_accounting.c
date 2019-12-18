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
struct TYPE_5__ {scalar_t__ cpu_usage_base; int /*<<< orphan*/  cpu_usage_last; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_INFINITY ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int unit_get_cpu_usage_raw (TYPE_1__*,scalar_t__*) ; 

int unit_reset_cpu_accounting(Unit *u) {
        int r;

        assert(u);

        u->cpu_usage_last = NSEC_INFINITY;

        r = unit_get_cpu_usage_raw(u, &u->cpu_usage_base);
        if (r < 0) {
                u->cpu_usage_base = 0;
                return r;
        }

        return 0;
}