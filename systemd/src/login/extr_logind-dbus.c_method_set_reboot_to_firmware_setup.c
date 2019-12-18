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
struct TYPE_8__ {int /*<<< orphan*/  polkit_registry; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int ENOENT ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  SD_BUS_ERROR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_verify_polkit_async (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int efi_reboot_to_firmware_supported () ; 
 int efi_set_reboot_to_firmware (int) ; 
 int errno ; 
 int getenv_bool (char*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int sd_bus_message_read (TYPE_1__*,char*,int*) ; 
 int sd_bus_reply_method_return (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int touch (char*) ; 
 scalar_t__ unlink (char*) ; 

__attribute__((used)) static int method_set_reboot_to_firmware_setup(
                sd_bus_message *message,
                void *userdata,
                sd_bus_error *error) {

        Manager *m = userdata;
        bool use_efi;
        int b, r;

        assert(message);
        assert(m);

        r = sd_bus_message_read(message, "b", &b);
        if (r < 0)
                return r;

        r = getenv_bool("SYSTEMD_REBOOT_TO_FIRMWARE_SETUP");
        if (r == -ENXIO) {
                /* EFI case: let's see what the firmware supports */

                r = efi_reboot_to_firmware_supported();
                if (r == -EOPNOTSUPP)
                        return sd_bus_error_setf(error, SD_BUS_ERROR_NOT_SUPPORTED, "Firmware does not support boot into firmware.");
                if (r < 0)
                        return r;

                use_efi = true;

        } else if (r <= 0) {
                /* non-EFI case: $SYSTEMD_REBOOT_TO_FIRMWARE_SETUP is set to off */

                if (r < 0)
                        log_warning_errno(r, "Failed to parse $SYSTEMD_REBOOT_TO_FIRMWARE_SETUP: %m");

                return sd_bus_error_setf(error, SD_BUS_ERROR_NOT_SUPPORTED, "Firmware does not support boot into firmware.");
        } else
                /* non-EFI case: $SYSTEMD_REBOOT_TO_FIRMWARE_SETUP is set to on */
                use_efi = false;

        r = bus_verify_polkit_async(message,
                                    CAP_SYS_ADMIN,
                                    "org.freedesktop.login1.set-reboot-to-firmware-setup",
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
                r = efi_set_reboot_to_firmware(b);
                if (r < 0)
                        return r;
        } else {
                if (b) {
                        r = touch("/run/systemd/reboot-to-firmware-setup");
                        if (r < 0)
                                return r;
                } else {
                        if (unlink("/run/systemd/reboot-to-firmware-setup") < 0 && errno != ENOENT)
                                return -errno;
                }
        }

        return sd_bus_reply_method_return(message, NULL);
}