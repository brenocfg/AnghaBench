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
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/ * CPU_ALLOC (size_t) ; 
 int /*<<< orphan*/  CPU_ALLOC_SIZE (size_t) ; 
 int CPU_COUNT_S (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_FREE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int SIZE_MAX ; 
 int errno ; 
 scalar_t__ sched_getaffinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cpus_in_affinity_mask(void) {
        size_t n = 16;
        int r;

        for (;;) {
                cpu_set_t *c;

                c = CPU_ALLOC(n);
                if (!c)
                        return -ENOMEM;

                if (sched_getaffinity(0, CPU_ALLOC_SIZE(n), c) >= 0) {
                        int k;

                        k = CPU_COUNT_S(CPU_ALLOC_SIZE(n), c);
                        CPU_FREE(c);

                        if (k <= 0)
                                return -EINVAL;

                        return k;
                }

                r = -errno;
                CPU_FREE(c);

                if (r != -EINVAL)
                        return r;
                if (n > SIZE_MAX/2)
                        return -ENOMEM;
                n *= 2;
        }
}