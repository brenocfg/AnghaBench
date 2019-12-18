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
typedef  int /*<<< orphan*/  SocketAddressBindIPv6Only ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET_ADDRESS_BOTH ; 
 int /*<<< orphan*/  SOCKET_ADDRESS_IPV6_ONLY ; 
 int parse_boolean (char const*) ; 
 int /*<<< orphan*/  socket_address_bind_ipv6_only_from_string (char const*) ; 

SocketAddressBindIPv6Only socket_address_bind_ipv6_only_or_bool_from_string(const char *n) {
        int r;

        r = parse_boolean(n);
        if (r > 0)
                return SOCKET_ADDRESS_IPV6_ONLY;
        if (r == 0)
                return SOCKET_ADDRESS_BOTH;

        return socket_address_bind_ipv6_only_from_string(n);
}