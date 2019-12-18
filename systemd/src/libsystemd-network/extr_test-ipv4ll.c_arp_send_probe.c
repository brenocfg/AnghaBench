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
struct ether_arp {int dummy; } ;
struct ether_addr {int dummy; } ;
typedef  scalar_t__ be32_t ;

/* Variables and functions */
 int arp_network_send_raw_socket (int,int,struct ether_arp*) ; 
 int /*<<< orphan*/  assert_se (int) ; 

int arp_send_probe(int fd, int ifindex,
                    be32_t pa, const struct ether_addr *ha) {
        struct ether_arp ea = {};

        assert_se(fd >= 0);
        assert_se(ifindex > 0);
        assert_se(pa != 0);
        assert_se(ha);

        return arp_network_send_raw_socket(fd, ifindex, &ea);
}