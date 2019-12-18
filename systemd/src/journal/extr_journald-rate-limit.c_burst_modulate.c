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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 unsigned int u64log2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned burst_modulate(unsigned burst, uint64_t available) {
        unsigned k;

        /* Modulates the burst rate a bit with the amount of available
         * disk space */

        k = u64log2(available);

        /* 1MB */
        if (k <= 20)
                return burst;

        burst = (burst * (k-16)) / 4;

        /*
         * Example:
         *
         *      <= 1MB = rate * 1
         *        16MB = rate * 2
         *       256MB = rate * 3
         *         4GB = rate * 4
         *        64GB = rate * 5
         *         1TB = rate * 6
         */

        return burst;
}