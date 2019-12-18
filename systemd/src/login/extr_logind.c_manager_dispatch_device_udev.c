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
typedef  int /*<<< orphan*/  sd_device_monitor ;
typedef  int /*<<< orphan*/  sd_device ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  manager_process_seat_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int manager_dispatch_device_udev(sd_device_monitor *monitor, sd_device *device, void *userdata) {
        Manager *m = userdata;

        assert(m);
        assert(device);

        manager_process_seat_device(m, device);
        return 0;
}