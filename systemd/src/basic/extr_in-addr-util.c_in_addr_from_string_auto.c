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
typedef  union in_addr_union {int dummy; } in_addr_union ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int EINVAL ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int in_addr_from_string (int,char const*,union in_addr_union*) ; 

int in_addr_from_string_auto(const char *s, int *ret_family, union in_addr_union *ret) {
        int r;

        assert(s);

        r = in_addr_from_string(AF_INET, s, ret);
        if (r >= 0) {
                if (ret_family)
                        *ret_family = AF_INET;
                return 0;
        }

        r = in_addr_from_string(AF_INET6, s, ret);
        if (r >= 0) {
                if (ret_family)
                        *ret_family = AF_INET6;
                return 0;
        }

        return -EINVAL;
}