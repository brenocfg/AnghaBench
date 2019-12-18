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

/* Variables and functions */
 scalar_t__ CGROUP_BLKIO_WEIGHT_INVALID ; 
 scalar_t__ CGROUP_BLKIO_WEIGHT_MAX ; 
 scalar_t__ CGROUP_BLKIO_WEIGHT_MIN ; 
 int ERANGE ; 
 scalar_t__ isempty (char const*) ; 
 int safe_atou64 (char const*,scalar_t__*) ; 

int cg_blkio_weight_parse(const char *s, uint64_t *ret) {
        uint64_t u;
        int r;

        if (isempty(s)) {
                *ret = CGROUP_BLKIO_WEIGHT_INVALID;
                return 0;
        }

        r = safe_atou64(s, &u);
        if (r < 0)
                return r;

        if (u < CGROUP_BLKIO_WEIGHT_MIN || u > CGROUP_BLKIO_WEIGHT_MAX)
                return -ERANGE;

        *ret = u;
        return 0;
}