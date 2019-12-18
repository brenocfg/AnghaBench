#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
union sockaddr_union {int /*<<< orphan*/  sa; TYPE_2__ in; } ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  be32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  assert (size_t) ; 
 int errno ; 
 int /*<<< orphan*/  htobe16 (int /*<<< orphan*/ ) ; 
 int sendto (int,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int dhcp_network_send_udp_socket(int s, be32_t address, uint16_t port,
                                 const void *packet, size_t len) {
        union sockaddr_union dest = {
                .in.sin_family = AF_INET,
                .in.sin_port = htobe16(port),
                .in.sin_addr.s_addr = address,
        };
        int r;

        assert(s >= 0);
        assert(packet);
        assert(len);

        r = sendto(s, packet, len, 0, &dest.sa, sizeof(dest.in));
        if (r < 0)
                return -errno;

        return 0;
}