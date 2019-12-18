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
struct ether_addr {int dummy; } ;
typedef  int /*<<< orphan*/  be32_t ;

/* Variables and functions */
 int arp_send_packet (int,int,int /*<<< orphan*/ ,struct ether_addr const*,int) ; 

int arp_send_probe(int fd, int ifindex,
                    be32_t pa, const struct ether_addr *ha) {
        return arp_send_packet(fd, ifindex, pa, ha, false);
}