#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  preference; } ;
typedef  TYPE_1__ sd_dhcp6_lease ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert_return (int /*<<< orphan*/ *,int) ; 

int dhcp6_lease_get_preference(sd_dhcp6_lease *lease, uint8_t *preference) {
        assert_return(preference, -EINVAL);

        if (!lease)
                return -EINVAL;

        *preference = lease->preference;

        return 0;
}