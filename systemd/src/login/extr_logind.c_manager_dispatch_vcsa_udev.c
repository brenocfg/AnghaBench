#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_device_monitor ;
struct TYPE_7__ {int /*<<< orphan*/  seat0; } ;
typedef  TYPE_1__ sd_device ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_ACTION_REMOVE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ device_for_action (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_device_get_sysname (TYPE_1__*,char const**) ; 
 int /*<<< orphan*/  seat_preallocate_vts (int /*<<< orphan*/ ) ; 
 scalar_t__ startswith (char const*,char*) ; 

__attribute__((used)) static int manager_dispatch_vcsa_udev(sd_device_monitor *monitor, sd_device *device, void *userdata) {
        Manager *m = userdata;
        const char *name;

        assert(m);
        assert(device);

        /* Whenever a VCSA device is removed try to reallocate our
         * VTs, to make sure our auto VTs never go away. */

        if (sd_device_get_sysname(device, &name) >= 0 &&
            startswith(name, "vcsa") &&
            device_for_action(device, DEVICE_ACTION_REMOVE))
                seat_preallocate_vts(m->seat0);

        return 0;
}