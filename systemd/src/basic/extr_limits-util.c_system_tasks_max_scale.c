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
typedef  int uint64_t ;

/* Variables and functions */
 int UINT64_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int system_tasks_max () ; 

uint64_t system_tasks_max_scale(uint64_t v, uint64_t max) {
        uint64_t t, m;

        assert(max > 0);

        /* Multiply the system's task value by the fraction v/max. Hence, if max==100 this calculates percentages
         * relative to the system's maximum number of tasks. Returns UINT64_MAX on overflow. */

        t = system_tasks_max();
        assert(t > 0);

        m = t * v;
        if (m / t != v) /* overflow? */
                return UINT64_MAX;

        return m / max;
}