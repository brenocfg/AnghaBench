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
struct TYPE_4__ {int property_devlinks_outdated; int /*<<< orphan*/  devlinks_generation; int /*<<< orphan*/ * devlinks; } ;
typedef  TYPE_1__ sd_device ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  set_free_free (int /*<<< orphan*/ *) ; 

void device_cleanup_devlinks(sd_device *device) {
        assert(device);

        set_free_free(device->devlinks);
        device->devlinks = NULL;
        device->property_devlinks_outdated = true;
        device->devlinks_generation++;
}