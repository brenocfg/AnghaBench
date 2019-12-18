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
struct TYPE_4__ {scalar_t__ devlink_priority; scalar_t__ watch_handle; int /*<<< orphan*/  tags; int /*<<< orphan*/  properties_db; int /*<<< orphan*/  devlinks; } ;
typedef  TYPE_1__ sd_device ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  ordered_hashmap_isempty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_isempty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool device_has_info(sd_device *device) {
        assert(device);

        if (!set_isempty(device->devlinks))
                return true;

        if (device->devlink_priority != 0)
                return true;

        if (!ordered_hashmap_isempty(device->properties_db))
                return true;

        if (!set_isempty(device->tags))
                return true;

        if (device->watch_handle >= 0)
                return true;

        return false;
}