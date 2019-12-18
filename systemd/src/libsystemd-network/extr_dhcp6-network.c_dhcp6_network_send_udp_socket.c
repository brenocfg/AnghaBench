#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
union sockaddr_union {int /*<<< orphan*/  sa; TYPE_1__ in6; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  DHCP6_PORT_SERVER ; 
 int /*<<< orphan*/  assert (struct in6_addr*) ; 
 int errno ; 
 int /*<<< orphan*/  htobe16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct in6_addr*,int) ; 
 int sendto (int,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int dhcp6_network_send_udp_socket(int s, struct in6_addr *server_address,
                                  const void *packet, size_t len) {
        union sockaddr_union dest = {
                .in6.sin6_family = AF_INET6,
                .in6.sin6_port = htobe16(DHCP6_PORT_SERVER),
        };
        int r;

        assert(server_address);

        memcpy(&dest.in6.sin6_addr, server_address, sizeof(dest.in6.sin6_addr));

        r = sendto(s, packet, len, 0, &dest.sa, sizeof(dest.in6));
        if (r < 0)
                return -errno;

        return 0;
}