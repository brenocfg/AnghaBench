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
typedef  scalar_t__ direction_t ;

/* Variables and functions */
 scalar_t__ DIRECTION_DOWN ; 

__attribute__((used)) static int bump_array_index(uint64_t *i, direction_t direction, uint64_t n) {

        /* Increase or decrease the specified index, in the right direction. */

        if (direction == DIRECTION_DOWN) {
                if (*i >= n - 1)
                        return 0;

                (*i) ++;
        } else {
                if (*i <= 0)
                        return 0;

                (*i) --;
        }

        return 1;
}