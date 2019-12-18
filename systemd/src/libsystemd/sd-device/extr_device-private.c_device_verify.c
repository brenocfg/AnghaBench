#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ action; scalar_t__ seqnum; int sealed; int /*<<< orphan*/  subsystem; int /*<<< orphan*/  devpath; } ;
typedef  TYPE_1__ sd_device ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_device_debug (TYPE_1__*,char*) ; 

__attribute__((used)) static int device_verify(sd_device *device) {
        assert(device);

        if (!device->devpath || !device->subsystem || device->action < 0 || device->seqnum == 0) {
                log_device_debug(device, "sd-device: Device created from strv or nulstr lacks devpath, subsystem, action or seqnum.");
                return -EINVAL;
        }

        device->sealed = true;

        return 0;
}