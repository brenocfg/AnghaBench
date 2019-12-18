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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ direction_t ;

/* Variables and functions */
 scalar_t__ DIRECTION_DOWN ; 

__attribute__((used)) static bool check_properly_ordered(uint64_t new_offset, uint64_t old_offset, direction_t direction) {

        /* Consider it an error if any of the two offsets is uninitialized */
        if (old_offset == 0 || new_offset == 0)
                return false;

        /* If we go down, the new offset must be larger than the old one. */
        return direction == DIRECTION_DOWN ?
                new_offset > old_offset  :
                new_offset < old_offset;
}