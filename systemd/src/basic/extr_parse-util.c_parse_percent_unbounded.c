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
 int EINVAL ; 
 int ERANGE ; 
 char* endswith (char const*,char*) ; 
 int safe_atoi (char const*,int*) ; 
 char* strndupa (char const*,int) ; 

int parse_percent_unbounded(const char *p) {
        const char *pc, *n;
        int r, v;

        pc = endswith(p, "%");
        if (!pc)
                return -EINVAL;

        n = strndupa(p, pc - p);
        r = safe_atoi(n, &v);
        if (r < 0)
                return r;
        if (v < 0)
                return -ERANGE;

        return v;
}