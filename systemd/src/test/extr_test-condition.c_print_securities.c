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
 int /*<<< orphan*/  is_efi_secure_boot () ; 
 int /*<<< orphan*/  log_info (char*,...) ; 
 int /*<<< orphan*/  mac_apparmor_use () ; 
 int /*<<< orphan*/  mac_selinux_use () ; 
 int /*<<< orphan*/  mac_smack_use () ; 
 int /*<<< orphan*/  mac_tomoyo_use () ; 
 int /*<<< orphan*/  use_audit () ; 
 int /*<<< orphan*/  use_ima () ; 
 int /*<<< orphan*/  yes_no (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_securities(void) {
        log_info("------ enabled security technologies ------");
        log_info("SELinux: %s", yes_no(mac_selinux_use()));
        log_info("AppArmor: %s", yes_no(mac_apparmor_use()));
        log_info("Tomoyo: %s", yes_no(mac_tomoyo_use()));
        log_info("IMA: %s", yes_no(use_ima()));
        log_info("SMACK: %s", yes_no(mac_smack_use()));
        log_info("Audit: %s", yes_no(use_audit()));
        log_info("UEFI secure boot: %s", yes_no(is_efi_secure_boot()));
        log_info("-------------------------------------------");
}