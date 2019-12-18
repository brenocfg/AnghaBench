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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int create_shutdown_run_nologin_or_warn () ; 
 int log_error_errno (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  log_setup_service () ; 
 int /*<<< orphan*/  mac_selinux_init () ; 
 scalar_t__ streq (char*,char*) ; 
 int /*<<< orphan*/  umask (int) ; 
 int unlink_or_warn (char*) ; 

__attribute__((used)) static int run(int argc, char *argv[]) {
        int r, k;

        if (argc != 2)
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "This program requires one argument.");

        log_setup_service();

        umask(0022);

        mac_selinux_init();

        if (streq(argv[1], "start")) {
                r = unlink_or_warn("/run/nologin");
                k = unlink_or_warn("/etc/nologin");
                if (r < 0)
                        return r;
                return k;

        } else if (streq(argv[1], "stop"))
                return create_shutdown_run_nologin_or_warn();

        return log_error_errno(SYNTHETIC_ERRNO(EINVAL), "Unknown verb '%s'.", argv[1]);
}