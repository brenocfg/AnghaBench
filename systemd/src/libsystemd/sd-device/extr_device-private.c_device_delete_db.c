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
typedef  int /*<<< orphan*/  sd_device ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int device_get_id_filename (int /*<<< orphan*/ *,char const**) ; 
 int errno ; 
 char* strjoina (char*,char const*) ; 
 int unlink (char*) ; 

int device_delete_db(sd_device *device) {
        const char *id;
        char *path;
        int r;

        assert(device);

        r = device_get_id_filename(device, &id);
        if (r < 0)
                return r;

        path = strjoina("/run/udev/data/", id);

        r = unlink(path);
        if (r < 0 && errno != ENOENT)
                return -errno;

        return 0;
}