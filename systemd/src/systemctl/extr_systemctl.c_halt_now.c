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
typedef  enum action { ____Placeholder_action } action ;

/* Variables and functions */
#define  ACTION_HALT 131 
#define  ACTION_KEXEC 130 
#define  ACTION_POWEROFF 129 
#define  ACTION_REBOOT 128 
 int /*<<< orphan*/  RB_ENABLE_CAD ; 
 int /*<<< orphan*/  RB_HALT_SYSTEM ; 
 int /*<<< orphan*/  RB_POWER_OFF ; 
 int REBOOT_DRY_RUN ; 
 int REBOOT_FALLBACK ; 
 int REBOOT_LOG ; 
 scalar_t__ arg_dry_run ; 
 int /*<<< orphan*/  arg_no_sync ; 
 int /*<<< orphan*/  arg_quiet ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int errno ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int /*<<< orphan*/  reboot (int /*<<< orphan*/ ) ; 
 int reboot_with_parameter (int) ; 
 int /*<<< orphan*/  sync () ; 

__attribute__((used)) static int halt_now(enum action a) {
        /* The kernel will automatically flush ATA disks and suchlike on reboot(), but the file systems need to be
         * synced explicitly in advance. */
        if (!arg_no_sync && !arg_dry_run)
                (void) sync();

        /* Make sure C-A-D is handled by the kernel from this point on... */
        if (!arg_dry_run)
                (void) reboot(RB_ENABLE_CAD);

        switch (a) {

        case ACTION_HALT:
                if (!arg_quiet)
                        log_info("Halting.");
                if (arg_dry_run)
                        return 0;
                (void) reboot(RB_HALT_SYSTEM);
                return -errno;

        case ACTION_POWEROFF:
                if (!arg_quiet)
                        log_info("Powering off.");
                if (arg_dry_run)
                        return 0;
                (void) reboot(RB_POWER_OFF);
                return -errno;

        case ACTION_KEXEC:
        case ACTION_REBOOT:
                return reboot_with_parameter(REBOOT_FALLBACK |
                                             (arg_quiet ? 0 : REBOOT_LOG) |
                                             (arg_dry_run ? REBOOT_DRY_RUN : 0));

        default:
                assert_not_reached("Unknown action.");
        }
}