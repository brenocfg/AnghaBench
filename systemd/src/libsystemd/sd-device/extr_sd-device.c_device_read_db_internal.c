#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ sealed; scalar_t__ db_loaded; } ;
typedef  TYPE_1__ sd_device ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int device_get_id_filename (TYPE_1__*,char const**) ; 
 int device_read_db_internal_filename (TYPE_1__*,char const*) ; 
 char* strjoina (char*,char const*) ; 

int device_read_db_internal(sd_device *device, bool force) {
        const char *id, *path;
        int r;

        assert(device);

        if (device->db_loaded || (!force && device->sealed))
                return 0;

        r = device_get_id_filename(device, &id);
        if (r < 0)
                return r;

        path = strjoina("/run/udev/data/", id);

        return device_read_db_internal_filename(device, path);
}