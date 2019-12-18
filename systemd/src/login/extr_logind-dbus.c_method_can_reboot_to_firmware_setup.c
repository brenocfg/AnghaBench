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
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int efi_reboot_to_firmware_supported () ; 
 int getenv_bool (char*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int return_test_polkit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int method_can_reboot_to_firmware_setup(
                sd_bus_message *message,
                void *userdata,
                sd_bus_error *error) {

        Manager *m = userdata;
        int r;

        assert(message);
        assert(m);

        r = getenv_bool("SYSTEMD_REBOOT_TO_FIRMWARE_SETUP");
        if (r == -ENXIO) {
                /* EFI case: let's see what the firmware supports */

                r = efi_reboot_to_firmware_supported();
                if (r < 0) {
                        if (r != -EOPNOTSUPP)
                                log_warning_errno(r, "Failed to determine whether reboot to firmware is supported: %m");

                        return sd_bus_reply_method_return(message, "s", "na");
                }

        } else if (r <= 0) {
                /* Non-EFI case: let's trust $SYSTEMD_REBOOT_TO_FIRMWARE_SETUP */

                if (r < 0)
                        log_warning_errno(r, "Failed to parse $SYSTEMD_REBOOT_TO_FIRMWARE_SETUP: %m");

                return sd_bus_reply_method_return(message, "s", "na");
        }

        return return_test_polkit(
                        message,
                        CAP_SYS_ADMIN,
                        "org.freedesktop.login1.set-reboot-to-firmware-setup",
                        NULL,
                        UID_INVALID,
                        error);
}