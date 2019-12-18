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
typedef  scalar_t__ usec_t ;

/* Variables and functions */
 scalar_t__ USEC_INFINITY ; 

__attribute__((used)) static inline usec_t usec_add(usec_t a, usec_t b) {
        usec_t c;

        /* Adds two time values, and makes sure USEC_INFINITY as input results as USEC_INFINITY in output, and doesn't
         * overflow. */

        c = a + b;
        if (c < a || c < b) /* overflow check */
                return USEC_INFINITY;

        return c;
}