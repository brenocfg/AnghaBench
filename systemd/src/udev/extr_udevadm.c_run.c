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
 int /*<<< orphan*/  LOG_REALM_SYSTEMD ; 
 int /*<<< orphan*/  log_get_max_level () ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 int /*<<< orphan*/  log_set_max_level_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_selinux_init () ; 
 int parse_argv (int,char**) ; 
 int /*<<< orphan*/  udev_parse_config () ; 
 int udevadm_main (int,char**) ; 

__attribute__((used)) static int run(int argc, char *argv[]) {
        int r;

        udev_parse_config();
        log_parse_environment();
        log_open();

        r = parse_argv(argc, argv);
        if (r <= 0)
                return r;

        log_set_max_level_realm(LOG_REALM_SYSTEMD, log_get_max_level());

        mac_selinux_init();
        return udevadm_main(argc, argv);
}