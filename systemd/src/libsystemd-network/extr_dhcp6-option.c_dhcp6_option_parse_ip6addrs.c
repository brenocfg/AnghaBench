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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GREEDY_REALLOC (struct in6_addr*,size_t,size_t) ; 
 int /*<<< orphan*/  memcpy (struct in6_addr*,int /*<<< orphan*/ *,int) ; 

int dhcp6_option_parse_ip6addrs(uint8_t *optval, uint16_t optlen,
                                struct in6_addr **addrs, size_t count,
                                size_t *allocated) {

        if (optlen == 0 || optlen % sizeof(struct in6_addr) != 0)
                return -EINVAL;

        if (!GREEDY_REALLOC(*addrs, *allocated,
                            count * sizeof(struct in6_addr) + optlen))
                return -ENOMEM;

        memcpy(*addrs + count, optval, optlen);

        count += optlen / sizeof(struct in6_addr);

        return count;
}