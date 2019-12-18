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
 int /*<<< orphan*/  assert (char const*) ; 
 int errno_from_name (char const*) ; 
 int /*<<< orphan*/  errno_is_valid (int) ; 
 int safe_atoi (char const*,int*) ; 

int parse_errno(const char *t) {
        int r, e;

        assert(t);

        r = errno_from_name(t);
        if (r > 0)
                return r;

        r = safe_atoi(t, &e);
        if (r < 0)
                return r;

        /* 0 is also allowed here */
        if (!errno_is_valid(e) && e != 0)
                return -ERANGE;

        return e;
}