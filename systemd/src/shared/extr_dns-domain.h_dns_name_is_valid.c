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
 int dns_name_normalize (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int dns_name_is_valid(const char *s) {
        int r;

        /* dns_name_normalize() verifies as a side effect */
        r = dns_name_normalize(s, 0, NULL);
        if (r == -EINVAL)
                return 0;
        if (r < 0)
                return r;
        return 1;
}