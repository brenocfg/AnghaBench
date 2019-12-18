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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {size_t serverid_len; int /*<<< orphan*/ * serverid; } ;
typedef  TYPE_1__ sd_dhcp6_lease ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ENOMSG ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 

int dhcp6_lease_get_serverid(sd_dhcp6_lease *lease, uint8_t **id, size_t *len) {
        assert_return(lease, -EINVAL);

        if (!lease->serverid)
                return -ENOMSG;

        if (id)
                *id = lease->serverid;
        if (len)
                *len = lease->serverid_len;

        return 0;
}