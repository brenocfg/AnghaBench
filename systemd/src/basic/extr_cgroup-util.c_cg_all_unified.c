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
 int CGROUP_UNIFIED_ALL ; 
 int cg_unified_cached (int) ; 

int cg_all_unified(void) {
        int r;

        r = cg_unified_cached(false);
        if (r < 0)
                return r;

        return r >= CGROUP_UNIFIED_ALL;
}