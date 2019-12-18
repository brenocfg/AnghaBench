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
struct TYPE_5__ {scalar_t__ devgid; } ;
typedef  TYPE_1__ sd_device ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int device_read_db (TYPE_1__*) ; 

int device_get_devnode_gid(sd_device *device, gid_t *gid) {
        int r;

        assert(device);

        r = device_read_db(device);
        if (r < 0)
                return r;

        if (device->devgid == (gid_t) -1)
                return -ENOENT;

        if (gid)
                *gid = device->devgid;

        return 0;
}