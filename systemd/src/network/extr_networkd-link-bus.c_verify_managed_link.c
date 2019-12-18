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
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  ifname; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ERROR_LINK_BUSY ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int verify_managed_link(Link *l, sd_bus_error *error) {
        assert(l);

        if (l->flags & IFF_LOOPBACK)
                return sd_bus_error_setf(error, BUS_ERROR_LINK_BUSY, "Link %s is loopback device.", l->ifname);

        return 0;
}