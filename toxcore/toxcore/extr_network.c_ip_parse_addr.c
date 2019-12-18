#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int dummy; } ;
typedef  struct in_addr in6_addr ;
struct TYPE_3__ {scalar_t__ family; int /*<<< orphan*/  ip6; int /*<<< orphan*/  ip4; } ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/ * inet_ntop (scalar_t__,struct in_addr*,char*,size_t) ; 

int ip_parse_addr(const IP *ip, char *address, size_t length)
{
    if (!address || !ip) {
        return 0;
    }

    if (ip->family == AF_INET) {
        struct in_addr *addr = (struct in_addr *)&ip->ip4;
        return inet_ntop(ip->family, addr, address, length) != NULL;
    } else if (ip->family == AF_INET6) {
        struct in6_addr *addr = (struct in6_addr *)&ip->ip6;
        return inet_ntop(ip->family, addr, address, length) != NULL;
    }

    return 0;
}