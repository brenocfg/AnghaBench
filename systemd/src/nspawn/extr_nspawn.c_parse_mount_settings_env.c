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

/* Variables and functions */
 int ENXIO ; 
 int MOUNT_APPLY_APIVFS_NETNS ; 
 int MOUNT_APPLY_APIVFS_RO ; 
 int MOUNT_APPLY_TMPFS_TMP ; 
 int /*<<< orphan*/  SET_FLAG (int,int,int) ; 
 int arg_mount_settings ; 
 char* getenv (char*) ; 
 int getenv_bool (char*) ; 
 int log_error_errno (int,char*) ; 
 int parse_boolean (char const*) ; 
 scalar_t__ streq_ptr (char const*,char*) ; 

__attribute__((used)) static int parse_mount_settings_env(void) {
        const char *e;
        int r;

        r = getenv_bool("SYSTEMD_NSPAWN_TMPFS_TMP");
        if (r < 0 && r != -ENXIO)
                return log_error_errno(r, "Failed to parse $SYSTEMD_NSPAWN_TMPFS_TMP: %m");
        if (r >= 0)
                SET_FLAG(arg_mount_settings, MOUNT_APPLY_TMPFS_TMP, r > 0);

        e = getenv("SYSTEMD_NSPAWN_API_VFS_WRITABLE");
        if (streq_ptr(e, "network"))
                arg_mount_settings |= MOUNT_APPLY_APIVFS_RO|MOUNT_APPLY_APIVFS_NETNS;

        else if (e) {
                r = parse_boolean(e);
                if (r < 0)
                        return log_error_errno(r, "Failed to parse $SYSTEMD_NSPAWN_API_VFS_WRITABLE: %m");

                SET_FLAG(arg_mount_settings, MOUNT_APPLY_APIVFS_RO, r == 0);
                SET_FLAG(arg_mount_settings, MOUNT_APPLY_APIVFS_NETNS, false);
        }

        return 0;
}