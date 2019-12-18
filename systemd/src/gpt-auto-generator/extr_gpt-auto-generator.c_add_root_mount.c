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
 int ENOENT ; 
 int /*<<< orphan*/  SPECIAL_INITRD_ROOT_FS_TARGET ; 
 int /*<<< orphan*/  SPECIAL_LOCAL_FS_TARGET ; 
 int add_mount (char*,char*,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int add_root_cryptsetup () ; 
 int /*<<< orphan*/  arg_dest ; 
 scalar_t__ arg_root_rw ; 
 int efi_loader_get_device_part_uuid (int /*<<< orphan*/ *) ; 
 int generator_write_initrd_root_device_deps (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ in_initrd () ; 
 int /*<<< orphan*/  is_efi_boot () ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int log_error_errno (int,char*) ; 

__attribute__((used)) static int add_root_mount(void) {

#if ENABLE_EFI
        int r;

        if (!is_efi_boot()) {
                log_debug("Not a EFI boot, not creating root mount.");
                return 0;
        }

        r = efi_loader_get_device_part_uuid(NULL);
        if (r == -ENOENT) {
                log_debug("EFI loader partition unknown, exiting.");
                return 0;
        } else if (r < 0)
                return log_error_errno(r, "Failed to read ESP partition UUID: %m");

        /* OK, we have an ESP partition, this is fantastic, so let's
         * wait for a root device to show up. A udev rule will create
         * the link for us under the right name. */

        if (in_initrd()) {
                r = generator_write_initrd_root_device_deps(arg_dest, "/dev/gpt-auto-root");
                if (r < 0)
                        return 0;

                r = add_root_cryptsetup();
                if (r < 0)
                        return r;
        }

        /* Note that we do not need to enable systemd-remount-fs.service here. If
         * /etc/fstab exists, systemd-fstab-generator will pull it in for us. */

        return add_mount(
                        "root",
                        "/dev/gpt-auto-root",
                        in_initrd() ? "/sysroot" : "/",
                        NULL,
                        arg_root_rw > 0,
                        NULL,
                        "Root Partition",
                        in_initrd() ? SPECIAL_INITRD_ROOT_FS_TARGET : SPECIAL_LOCAL_FS_TARGET);
#else
        return 0;
#endif
}