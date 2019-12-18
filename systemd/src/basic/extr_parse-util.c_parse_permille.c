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
 int ERANGE ; 
 int parse_permille_unbounded (char const*) ; 

int parse_permille(const char *p) {
        int v;

        v = parse_permille_unbounded(p);
        if (v > 1000)
                return -ERANGE;

        return v;
}