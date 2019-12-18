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

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 int errno ; 
 scalar_t__ send (int,struct ether_arp const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arp_network_send_raw_socket(int fd, int ifindex,
                                       const struct ether_arp *arp) {
        assert_se(arp);
        assert_se(ifindex > 0);
        assert_se(fd >= 0);

        if (send(fd, arp, sizeof(struct ether_arp), 0) < 0)
                return -errno;

        return 0;
}