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
 int /*<<< orphan*/  STR_IN_SET (char*,char*,char*) ; 
 int SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int do_mount (char*) ; 
 int do_umount (char*) ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 int mac_selinux_init () ; 
 scalar_t__ streq (char*,char*) ; 
 int /*<<< orphan*/  umask (int) ; 

__attribute__((used)) static int run(int argc, char *argv[]) {
        int r;

        log_parse_environment();
        log_open();

        if (argc != 3)
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "This program takes two arguments.");
        if (!STR_IN_SET(argv[1], "start", "stop"))
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "First argument must be either \"start\" or \"stop\".");

        r = mac_selinux_init();
        if (r < 0)
                return log_error_errno(r, "Could not initialize labelling: %m\n");

        umask(0022);

        if (streq(argv[1], "start"))
                return do_mount(argv[2]);
        if (streq(argv[1], "stop"))
                return do_umount(argv[2]);
        assert_not_reached("Unknown verb!");
}