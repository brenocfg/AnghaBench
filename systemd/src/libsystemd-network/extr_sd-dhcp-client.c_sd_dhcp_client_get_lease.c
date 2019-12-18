#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_dhcp_lease ;
struct TYPE_4__ {int /*<<< orphan*/ * lease; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ sd_dhcp_client ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP_STATE_BOUND ; 
 int /*<<< orphan*/  DHCP_STATE_REBINDING ; 
 int /*<<< orphan*/  DHCP_STATE_RENEWING ; 
 int /*<<< orphan*/  DHCP_STATE_SELECTING ; 
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 

int sd_dhcp_client_get_lease(sd_dhcp_client *client, sd_dhcp_lease **ret) {
        assert_return(client, -EINVAL);

        if (!IN_SET(client->state, DHCP_STATE_SELECTING, DHCP_STATE_BOUND, DHCP_STATE_RENEWING, DHCP_STATE_REBINDING))
                return -EADDRNOTAVAIL;

        if (ret)
                *ret = client->lease;

        return 0;
}