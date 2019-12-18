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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  be32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int SOCK_CLOEXEC ; 
 int SOCK_DGRAM ; 
 int SOCK_NONBLOCK ; 
 int errno ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int dhcp_network_bind_udp_socket(int ifindex, be32_t address, uint16_t port, int ip_service_type) {
        int fd;

        fd = socket(AF_INET, SOCK_DGRAM | SOCK_CLOEXEC | SOCK_NONBLOCK, 0);
        if (fd < 0)
                return -errno;

        return fd;
}