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
 int /*<<< orphan*/  device_ensure_usec_initialized (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int event_queue_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_queue_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_device_error_errno (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int on_uevent(sd_device_monitor *monitor, sd_device *dev, void *userdata) {
        Manager *manager = userdata;
        int r;

        assert(manager);

        device_ensure_usec_initialized(dev, NULL);

        r = event_queue_insert(manager, dev);
        if (r < 0) {
                log_device_error_errno(dev, r, "Failed to insert device into event queue: %m");
                return 1;
        }

        /* we have fresh events, try to schedule them */
        event_queue_start(manager);

        return 1;
}