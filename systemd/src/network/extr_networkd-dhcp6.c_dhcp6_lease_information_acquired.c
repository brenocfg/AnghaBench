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
typedef  int /*<<< orphan*/  sd_dhcp6_client ;
typedef  int /*<<< orphan*/  Link ;

/* Variables and functions */

__attribute__((used)) static int dhcp6_lease_information_acquired(sd_dhcp6_client *client,
                                        Link *link) {
        return 0;
}