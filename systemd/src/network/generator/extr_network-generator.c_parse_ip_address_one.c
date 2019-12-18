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
 int AF_INET6 ; 
 int EINVAL ; 
 int in_addr_from_string (int,char const*,union in_addr_union*) ; 
 char* strchr (char const*,char) ; 
 char* strndupa (char const*,int) ; 

__attribute__((used)) static int parse_ip_address_one(int family, const char **value, union in_addr_union *ret) {
        const char *p = *value, *q, *buf;
        int r;

        if (p[0] == ':') {
                *value = p + 1;
                return 0;
        }

        if (family == AF_INET6) {
                if (p[0] != '[')
                        return -EINVAL;

                q = strchr(p + 1, ']');
                if (!q)
                        return -EINVAL;

                if (q[1] != ':')
                        return -EINVAL;

                buf = strndupa(p + 1, q - p - 1);
                p = q + 2;
        } else {
                q = strchr(p, ':');
                if (!q)
                        return -EINVAL;

                buf = strndupa(p, q - p);
                p = q + 1;
        }

        r = in_addr_from_string(family, buf, ret);
        if (r < 0)
                return r;

        *value = p;
        return 1;
}