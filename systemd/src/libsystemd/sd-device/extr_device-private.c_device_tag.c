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
typedef  char const sd_device ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  GID_INVALID ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  USEC_INFINITY ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int device_get_id_filename (char const*,char const**) ; 
 int errno ; 
 char* strjoina (char*,char const*,char*,char const*) ; 
 int touch_file (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int unlink (char*) ; 

__attribute__((used)) static int device_tag(sd_device *device, const char *tag, bool add) {
        const char *id;
        char *path;
        int r;

        assert(device);
        assert(tag);

        r = device_get_id_filename(device, &id);
        if (r < 0)
                return r;

        path = strjoina("/run/udev/tags/", tag, "/", id);

        if (add) {
                r = touch_file(path, true, USEC_INFINITY, UID_INVALID, GID_INVALID, 0444);
                if (r < 0)
                        return r;
        } else {
                r = unlink(path);
                if (r < 0 && errno != ENOENT)
                        return -errno;
        }

        return 0;
}