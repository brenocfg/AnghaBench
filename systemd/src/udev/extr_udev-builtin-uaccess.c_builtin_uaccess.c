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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  sd_device ;

/* Variables and functions */
 int /*<<< orphan*/  ENODATA ; 
 int ENOENT ; 
 int /*<<< orphan*/  ENXIO ; 
 scalar_t__ IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int devnode_acl (char const*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_device_error_errno (int /*<<< orphan*/ *,int,char*,...) ; 
 int /*<<< orphan*/  log_device_full (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  logind_running () ; 
 int sd_device_get_devname (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ sd_device_get_property_value (int /*<<< orphan*/ *,char*,char const**) ; 
 int sd_seat_get_active (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umask (int) ; 

__attribute__((used)) static int builtin_uaccess(sd_device *dev, int argc, char *argv[], bool test) {
        const char *path = NULL, *seat;
        bool changed_acl = false;
        uid_t uid;
        int r;

        umask(0022);

        /* don't muck around with ACLs when the system is not running systemd */
        if (!logind_running())
                return 0;

        r = sd_device_get_devname(dev, &path);
        if (r < 0) {
                log_device_error_errno(dev, r, "Failed to get device name: %m");
                goto finish;
        }

        if (sd_device_get_property_value(dev, "ID_SEAT", &seat) < 0)
                seat = "seat0";

        r = sd_seat_get_active(seat, NULL, &uid);
        if (r < 0) {
                if (IN_SET(r, -ENXIO, -ENODATA))
                        /* No active session on this seat */
                        r = 0;
                else
                        log_device_error_errno(dev, r, "Failed to determine active user on seat %s: %m", seat);

                goto finish;
        }

        r = devnode_acl(path, true, false, 0, true, uid);
        if (r < 0) {
                log_device_full(dev, r == -ENOENT ? LOG_DEBUG : LOG_ERR, r, "Failed to apply ACL: %m");
                goto finish;
        }

        changed_acl = true;
        r = 0;

finish:
        if (path && !changed_acl) {
                int k;

                /* Better be safe than sorry and reset ACL */
                k = devnode_acl(path, true, false, 0, false, 0);
                if (k < 0) {
                        log_device_full(dev, k == -ENOENT ? LOG_DEBUG : LOG_ERR, k, "Failed to apply ACL: %m");
                        if (r >= 0)
                                r = k;
                }
        }

        return r;
}