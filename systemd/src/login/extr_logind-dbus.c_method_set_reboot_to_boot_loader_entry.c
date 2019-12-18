#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  polkit_registry; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  EFI_LOADER_FEATURE_ENTRY_ONESHOT ; 
 int /*<<< orphan*/  EFI_VENDOR_LOADER ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  SD_BUS_ERROR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int boot_loader_entry_exists (char const*) ; 
 int bus_verify_polkit_async (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ efi_loader_entry_name_valid (char const*) ; 
 int efi_loader_get_features (int /*<<< orphan*/ *) ; 
 int efi_set_variable (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int efi_set_variable_string (int /*<<< orphan*/ ,char*,char const*) ; 
 int errno ; 
 int getenv_bool (char*) ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int sd_bus_message_read (TYPE_1__*,char*,char const**) ; 
 int sd_bus_reply_method_return (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlink (char*) ; 
 int write_string_file_atomic_label (char*,char const*) ; 

__attribute__((used)) static int method_set_reboot_to_boot_loader_entry(
                sd_bus_message *message,
                void *userdata,
                sd_bus_error *error) {

        Manager *m = userdata;
        bool use_efi;
        const char *v;
        int r;

        assert(message);
        assert(m);

        r = sd_bus_message_read(message, "s", &v);
        if (r < 0)
                return r;

        if (isempty(v))
                v = NULL;
        else if (efi_loader_entry_name_valid(v)) {
                r = boot_loader_entry_exists(v);
                if (r < 0)
                        return r;
                if (r == 0)
                        return sd_bus_error_setf(error, SD_BUS_ERROR_NOT_SUPPORTED, "Boot loader entry '%s' is not known.", v);
        } else
                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Boot loader entry name '%s' is not valid, refusing.", v);

        r = getenv_bool("SYSTEMD_REBOOT_TO_BOOT_LOADER_ENTRY");
        if (r == -ENXIO) {
                uint64_t features;

                /* EFI case: let's see if booting into boot loader entry is supported. */

                r = efi_loader_get_features(&features);
                if (r < 0)
                        log_warning_errno(r, "Failed to determine whether reboot into boot loader entry is supported: %m");
                if (r < 0 || !FLAGS_SET(features, EFI_LOADER_FEATURE_ENTRY_ONESHOT))
                        return sd_bus_error_setf(error, SD_BUS_ERROR_NOT_SUPPORTED, "Loader does not support boot into boot loader entry.");

                use_efi = true;

        } else if (r <= 0) {
                /* non-EFI case: $SYSTEMD_REBOOT_TO_BOOT_LOADER_ENTRY is set to off */

                if (r < 0)
                        log_warning_errno(r, "Failed to parse $SYSTEMD_REBOOT_TO_BOOT_LOADER_ENTRY: %m");

                return sd_bus_error_setf(error, SD_BUS_ERROR_NOT_SUPPORTED, "Loader does not support boot into boot loader entry.");
        } else
                /* non-EFI case: $SYSTEMD_REBOOT_TO_BOOT_LOADER_ENTRY is set to on */
                use_efi = false;

        r = bus_verify_polkit_async(message,
                                    CAP_SYS_ADMIN,
                                    "org.freedesktop.login1.set-reboot-to-boot-loader-entry",
                                    NULL,
                                    false,
                                    UID_INVALID,
                                    &m->polkit_registry,
                                    error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* No authorization for now, but the async polkit stuff will call us again when it has it */

        if (use_efi) {
                if (isempty(v))
                        /* Delete item */
                        r = efi_set_variable(EFI_VENDOR_LOADER, "LoaderEntryOneShot", NULL, 0);
                else
                        r = efi_set_variable_string(EFI_VENDOR_LOADER, "LoaderEntryOneShot", v);
                if (r < 0)
                        return r;
        } else {
                if (isempty(v)) {
                        if (unlink("/run/systemd/reboot-to-boot-loader-entry") < 0 && errno != ENOENT)
                                return -errno;
                } else {
                        r = write_string_file_atomic_label("/run/systemd/reboot-boot-to-loader-entry", v);
                        if (r < 0)
                                return r;
                }
        }

        return sd_bus_reply_method_return(message, NULL);
}