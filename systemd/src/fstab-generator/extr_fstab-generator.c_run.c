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
 int add_sysroot_mount () ; 
 int add_sysroot_usr_mount () ; 
 int add_volatile_root () ; 
 int add_volatile_var () ; 
 char const* arg_dest ; 
 char const* arg_dest_late ; 
 scalar_t__ arg_fstab_enabled ; 
 int /*<<< orphan*/  assert_se (char const*) ; 
 int /*<<< orphan*/  determine_root () ; 
 int generator_enable_remount_fs_service (char const*) ; 
 scalar_t__ in_initrd () ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int parse_fstab (int) ; 
 int /*<<< orphan*/  parse_proc_cmdline_item ; 
 int proc_cmdline_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run(const char *dest, const char *dest_early, const char *dest_late) {
        int r, r2 = 0, r3 = 0;

        assert_se(arg_dest = dest);
        assert_se(arg_dest_late = dest_late);

        r = proc_cmdline_parse(parse_proc_cmdline_item, NULL, 0);
        if (r < 0)
                log_warning_errno(r, "Failed to parse kernel command line, ignoring: %m");

        (void) determine_root();

        /* Always honour root= and usr= in the kernel command line if we are in an initrd */
        if (in_initrd()) {
                r = add_sysroot_mount();

                r2 = add_sysroot_usr_mount();

                r3 = add_volatile_root();
        } else
                r = add_volatile_var();

        /* Honour /etc/fstab only when that's enabled */
        if (arg_fstab_enabled) {
                /* Parse the local /etc/fstab, possibly from the initrd */
                r2 = parse_fstab(false);

                /* If running in the initrd also parse the /etc/fstab from the host */
                if (in_initrd())
                        r3 = parse_fstab(true);
                else
                        r3 = generator_enable_remount_fs_service(arg_dest);
        }

        return r < 0 ? r : r2 < 0 ? r2 : r3;
}