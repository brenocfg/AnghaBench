#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_device_monitor ;
struct TYPE_9__ {int /*<<< orphan*/ * worker_watch; } ;
typedef  TYPE_1__ sd_device ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 size_t WRITE_END ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int device_monitor_send_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  log_device_warning_errno (TYPE_1__*,int,char*) ; 
 int worker_process_device (TYPE_1__*,TYPE_1__*) ; 
 int worker_send_message (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int worker_device_monitor_handler(sd_device_monitor *monitor, sd_device *dev, void *userdata) {
        Manager *manager = userdata;
        int r;

        assert(dev);
        assert(manager);

        r = worker_process_device(manager, dev);
        if (r < 0)
                log_device_warning_errno(dev, r, "Failed to process device, ignoring: %m");

        /* send processed event back to libudev listeners */
        r = device_monitor_send_device(monitor, NULL, dev);
        if (r < 0)
                log_device_warning_errno(dev, r, "Failed to send device, ignoring: %m");

        /* send udevd the result of the event execution */
        r = worker_send_message(manager->worker_watch[WRITE_END]);
        if (r < 0)
                log_device_warning_errno(dev, r, "Failed to send signal to main daemon, ignoring: %m");

        return 1;
}