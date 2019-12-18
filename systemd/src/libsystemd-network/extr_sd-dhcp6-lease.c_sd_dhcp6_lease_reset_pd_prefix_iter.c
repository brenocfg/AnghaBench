#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  addresses; } ;
struct TYPE_5__ {TYPE_1__ pd; int /*<<< orphan*/  prefix_iter; } ;
typedef  TYPE_2__ sd_dhcp6_lease ;

/* Variables and functions */

void sd_dhcp6_lease_reset_pd_prefix_iter(sd_dhcp6_lease *lease) {
        if (lease)
                lease->prefix_iter = lease->pd.addresses;
}