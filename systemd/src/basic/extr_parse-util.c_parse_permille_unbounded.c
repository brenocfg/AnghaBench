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
 int INT_MAX ; 
 char* endswith (char const*,char*) ; 
 char* memchr (char const*,char,int) ; 
 int safe_atoi (char const*,int*) ; 
 char* strndupa (char const*,int) ; 

int parse_permille_unbounded(const char *p) {
        const char *pc, *pm, *dot, *n;
        int r, q, v;

        pm = endswith(p, "‰");
        if (pm) {
                n = strndupa(p, pm - p);
                r = safe_atoi(n, &v);
                if (r < 0)
                        return r;
                if (v < 0)
                        return -ERANGE;
        } else {
                pc = endswith(p, "%");
                if (!pc)
                        return -EINVAL;

                dot = memchr(p, '.', pc - p);
                if (dot) {
                        if (dot + 2 != pc)
                                return -EINVAL;
                        if (dot[1] < '0' || dot[1] > '9')
                                return -EINVAL;
                        q = dot[1] - '0';
                        n = strndupa(p, dot - p);
                } else {
                        q = 0;
                        n = strndupa(p, pc - p);
                }
                r = safe_atoi(n, &v);
                if (r < 0)
                        return r;
                if (v < 0)
                        return -ERANGE;
                if (v > (INT_MAX - q) / 10)
                        return -ERANGE;

                v = v * 10 + q;
        }

        return v;
}