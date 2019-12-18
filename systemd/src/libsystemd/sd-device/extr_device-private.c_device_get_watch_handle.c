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
struct TYPE_5__ {int watch_handle; } ;
typedef  TYPE_1__ sd_device ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int device_read_db (TYPE_1__*) ; 

int device_get_watch_handle(sd_device *device, int *handle) {
        int r;

        assert(device);

        r = device_read_db(device);
        if (r < 0)
                return r;

        if (device->watch_handle < 0)
                return -ENOENT;

        if (handle)
                *handle = device->watch_handle;

        return 0;
}