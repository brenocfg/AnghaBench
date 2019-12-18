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
typedef  void sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  void sd_bus ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (void*) ; 
 int efi_get_reboot_to_firmware () ; 
 int errno ; 
 int getenv_bool (char*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int sd_bus_message_append (void*,char*,int) ; 

__attribute__((used)) static int property_get_reboot_to_firmware_setup(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {
        int r;

        assert(bus);
        assert(reply);
        assert(userdata);

        r = getenv_bool("SYSTEMD_REBOOT_TO_FIRMWARE_SETUP");
        if (r == -ENXIO) {
                /* EFI case: let's see what is currently configured in the EFI variables */
                r = efi_get_reboot_to_firmware();
                if (r < 0 && r != -EOPNOTSUPP)
                        log_warning_errno(r, "Failed to determine reboot-to-firmware-setup state: %m");
        } else if (r < 0)
                log_warning_errno(r, "Failed to parse $SYSTEMD_REBOOT_TO_FIRMWARE_SETUP: %m");
        else if (r > 0) {
                /* Non-EFI case: let's see whether /run/systemd/reboot-to-firmware-setup exists. */
                if (access("/run/systemd/reboot-to-firmware-setup", F_OK) < 0) {
                        if (errno != ENOENT)
                                log_warning_errno(errno, "Failed to check whether /run/systemd/reboot-to-firmware-setup exists: %m");

                        r = false;
                } else
                        r = true;
        }

        return sd_bus_message_append(reply, "b", r > 0);
}