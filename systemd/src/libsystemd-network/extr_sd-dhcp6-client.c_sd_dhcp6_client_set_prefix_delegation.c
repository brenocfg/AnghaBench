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
struct TYPE_4__ {int /*<<< orphan*/  request; } ;
typedef  TYPE_1__ sd_dhcp6_client ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP6_REQUEST_IA_PD ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SET_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 

int sd_dhcp6_client_set_prefix_delegation(sd_dhcp6_client *client, int delegation) {
        assert_return(client, -EINVAL);

        SET_FLAG(client->request, DHCP6_REQUEST_IA_PD, delegation);

        return 0;
}