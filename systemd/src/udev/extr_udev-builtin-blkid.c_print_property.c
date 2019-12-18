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
typedef  int /*<<< orphan*/  s ;

/* Variables and functions */
 int /*<<< orphan*/  blkid_encode_string (char const*,char*,int) ; 
 int /*<<< orphan*/  blkid_safe_string (char const*,char*,int) ; 
 scalar_t__ startswith (char const*,char*) ; 
 scalar_t__ streq (char const*,char*) ; 
 int /*<<< orphan*/  strscpyl (char*,int,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udev_builtin_add_property (int /*<<< orphan*/ *,int,char*,char const*) ; 

__attribute__((used)) static void print_property(sd_device *dev, bool test, const char *name, const char *value) {
        char s[256];

        s[0] = '\0';

        if (streq(name, "TYPE")) {
                udev_builtin_add_property(dev, test, "ID_FS_TYPE", value);

        } else if (streq(name, "USAGE")) {
                udev_builtin_add_property(dev, test, "ID_FS_USAGE", value);

        } else if (streq(name, "VERSION")) {
                udev_builtin_add_property(dev, test, "ID_FS_VERSION", value);

        } else if (streq(name, "UUID")) {
                blkid_safe_string(value, s, sizeof(s));
                udev_builtin_add_property(dev, test, "ID_FS_UUID", s);
                blkid_encode_string(value, s, sizeof(s));
                udev_builtin_add_property(dev, test, "ID_FS_UUID_ENC", s);

        } else if (streq(name, "UUID_SUB")) {
                blkid_safe_string(value, s, sizeof(s));
                udev_builtin_add_property(dev, test, "ID_FS_UUID_SUB", s);
                blkid_encode_string(value, s, sizeof(s));
                udev_builtin_add_property(dev, test, "ID_FS_UUID_SUB_ENC", s);

        } else if (streq(name, "LABEL")) {
                blkid_safe_string(value, s, sizeof(s));
                udev_builtin_add_property(dev, test, "ID_FS_LABEL", s);
                blkid_encode_string(value, s, sizeof(s));
                udev_builtin_add_property(dev, test, "ID_FS_LABEL_ENC", s);

        } else if (streq(name, "PTTYPE")) {
                udev_builtin_add_property(dev, test, "ID_PART_TABLE_TYPE", value);

        } else if (streq(name, "PTUUID")) {
                udev_builtin_add_property(dev, test, "ID_PART_TABLE_UUID", value);

        } else if (streq(name, "PART_ENTRY_NAME")) {
                blkid_encode_string(value, s, sizeof(s));
                udev_builtin_add_property(dev, test, "ID_PART_ENTRY_NAME", s);

        } else if (streq(name, "PART_ENTRY_TYPE")) {
                blkid_encode_string(value, s, sizeof(s));
                udev_builtin_add_property(dev, test, "ID_PART_ENTRY_TYPE", s);

        } else if (startswith(name, "PART_ENTRY_")) {
                strscpyl(s, sizeof(s), "ID_", name, NULL);
                udev_builtin_add_property(dev, test, s, value);

        } else if (streq(name, "SYSTEM_ID")) {
                blkid_encode_string(value, s, sizeof(s));
                udev_builtin_add_property(dev, test, "ID_FS_SYSTEM_ID", s);

        } else if (streq(name, "PUBLISHER_ID")) {
                blkid_encode_string(value, s, sizeof(s));
                udev_builtin_add_property(dev, test, "ID_FS_PUBLISHER_ID", s);

        } else if (streq(name, "APPLICATION_ID")) {
                blkid_encode_string(value, s, sizeof(s));
                udev_builtin_add_property(dev, test, "ID_FS_APPLICATION_ID", s);

        } else if (streq(name, "BOOT_SYSTEM_ID")) {
                blkid_encode_string(value, s, sizeof(s));
                udev_builtin_add_property(dev, test, "ID_FS_BOOT_SYSTEM_ID", s);
        }
}