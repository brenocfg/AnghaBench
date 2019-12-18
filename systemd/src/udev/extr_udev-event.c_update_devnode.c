#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_device ;
struct TYPE_3__ {int mode; int /*<<< orphan*/  seclabel_list; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  dev_db_clone; int /*<<< orphan*/ * dev; } ;
typedef  TYPE_1__ UdevEvent ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_ACTION_ADD ; 
 int ENOENT ; 
 int MODE_INVALID ; 
 int device_for_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int device_get_devnode_gid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int device_get_devnode_mode (int /*<<< orphan*/ *,int*) ; 
 int device_get_devnode_uid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gid_is_valid (int /*<<< orphan*/ ) ; 
 int log_device_error_errno (int /*<<< orphan*/ *,int,char*) ; 
 int sd_device_get_devnum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int udev_node_add (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_node_update_old_links (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_is_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_devnode(UdevEvent *event) {
        sd_device *dev = event->dev;
        int r;

        r = sd_device_get_devnum(dev, NULL);
        if (r == -ENOENT)
                return 0;
        if (r < 0)
                return log_device_error_errno(dev, r, "Failed to get devnum: %m");

        /* remove/update possible left-over symlinks from old database entry */
        if (event->dev_db_clone)
                (void) udev_node_update_old_links(dev, event->dev_db_clone);

        if (!uid_is_valid(event->uid)) {
                r = device_get_devnode_uid(dev, &event->uid);
                if (r < 0 && r != -ENOENT)
                        return log_device_error_errno(dev, r, "Failed to get devnode UID: %m");
        }

        if (!gid_is_valid(event->gid)) {
                r = device_get_devnode_gid(dev, &event->gid);
                if (r < 0 && r != -ENOENT)
                        return log_device_error_errno(dev, r, "Failed to get devnode GID: %m");
        }

        if (event->mode == MODE_INVALID) {
                r = device_get_devnode_mode(dev, &event->mode);
                if (r < 0 && r != -ENOENT)
                        return log_device_error_errno(dev, r, "Failed to get devnode mode: %m");
        }
        if (event->mode == MODE_INVALID && gid_is_valid(event->gid) && event->gid > 0)
                /* If group is set, but mode is not set, "upgrade" mode for the group. */
                event->mode = 0660;

        bool apply_mac = device_for_action(dev, DEVICE_ACTION_ADD);

        return udev_node_add(dev, apply_mac, event->mode, event->uid, event->gid, event->seclabel_list);
}