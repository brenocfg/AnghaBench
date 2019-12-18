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
typedef  size_t uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int AF_INET6 ; 
 int ERANGE ; 
 size_t IPV4_MIN_MTU ; 
 size_t IPV6_MIN_MTU ; 
 size_t UINT32_MAX ; 
 int parse_size (char const*,int,size_t*) ; 

int parse_mtu(int family, const char *s, uint32_t *ret) {
        uint64_t u;
        size_t m;
        int r;

        r = parse_size(s, 1024, &u);
        if (r < 0)
                return r;

        if (u > UINT32_MAX)
                return -ERANGE;

        if (family == AF_INET6)
                m = IPV6_MIN_MTU; /* This is 1280 */
        else
                m = IPV4_MIN_MTU; /* For all other protocols, including 'unspecified' we assume the IPv4 minimal MTU */

        if (u < m)
                return -ERANGE;

        *ret = (uint32_t) u;
        return 0;
}