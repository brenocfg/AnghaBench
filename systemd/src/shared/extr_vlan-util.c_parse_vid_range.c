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
typedef  unsigned int uint16_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int VLANID_MAX ; 
 int parse_range (char const*,unsigned int*,unsigned int*) ; 

int parse_vid_range(const char *p, uint16_t *vid, uint16_t *vid_end) {
        unsigned lower, upper;
        int r;

        r = parse_range(p, &lower, &upper);
        if (r < 0)
                return r;

        if (lower > VLANID_MAX || upper > VLANID_MAX || lower > upper)
                return -EINVAL;

        *vid = lower;
        *vid_end = upper;
        return 0;
}