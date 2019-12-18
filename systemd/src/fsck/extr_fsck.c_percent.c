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

/* Variables and functions */
 unsigned int ELEMENTSOF (int const*) ; 

__attribute__((used)) static double percent(int pass, unsigned long cur, unsigned long max) {
        /* Values stolen from e2fsck */

        static const int pass_table[] = {
                0, 70, 90, 92, 95, 100
        };

        if (pass <= 0)
                return 0.0;

        if ((unsigned) pass >= ELEMENTSOF(pass_table) || max == 0)
                return 100.0;

        return (double) pass_table[pass-1] +
                ((double) pass_table[pass] - (double) pass_table[pass-1]) *
                (double) cur / (double) max;
}