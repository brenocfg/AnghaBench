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
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ errno ; 
 int errno_or_else (int /*<<< orphan*/ ) ; 
 scalar_t__ inet_pton (int,char const*,union in_addr_union*) ; 

int in_addr_from_string(int family, const char *s, union in_addr_union *ret) {
        union in_addr_union buffer;
        assert(s);

        if (!IN_SET(family, AF_INET, AF_INET6))
                return -EAFNOSUPPORT;

        errno = 0;
        if (inet_pton(family, s, ret ?: &buffer) <= 0)
                return errno_or_else(EINVAL);

        return 0;
}