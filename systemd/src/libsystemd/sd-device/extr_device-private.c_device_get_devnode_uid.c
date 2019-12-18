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
typedef  scalar_t__ uid_t ;
struct TYPE_5__ {scalar_t__ devuid; } ;
typedef  TYPE_1__ sd_device ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int device_read_db (TYPE_1__*) ; 

int device_get_devnode_uid(sd_device *device, uid_t *uid) {
        int r;

        assert(device);

        r = device_read_db(device);
        if (r < 0)
                return r;

        if (device->devuid == (uid_t) -1)
                return -ENOENT;

        if (uid)
                *uid = device->devuid;

        return 0;
}