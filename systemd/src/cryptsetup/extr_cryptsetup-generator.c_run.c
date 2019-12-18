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
 int /*<<< orphan*/  PROC_CMDLINE_STRIP_RD_PREFIX ; 
 int add_crypttab_devices () ; 
 int add_proc_cmdline_devices () ; 
 char* arg_crypttab ; 
 char const* arg_dest ; 
 int /*<<< orphan*/  arg_disks ; 
 int /*<<< orphan*/  arg_enabled ; 
 char* arg_runtime_directory ; 
 int /*<<< orphan*/  assert_se (char const*) ; 
 int /*<<< orphan*/  crypt_device_hash_ops ; 
 scalar_t__ getenv (char*) ; 
 int /*<<< orphan*/  hashmap_new (int /*<<< orphan*/ *) ; 
 int log_oom () ; 
 int log_warning_errno (int,char*) ; 
 int /*<<< orphan*/  parse_proc_cmdline_item ; 
 int proc_cmdline_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run(const char *dest, const char *dest_early, const char *dest_late) {
        int r;

        assert_se(arg_dest = dest);

        arg_crypttab = getenv("SYSTEMD_CRYPTTAB") ?: "/etc/crypttab";
        arg_runtime_directory = getenv("RUNTIME_DIRECTORY") ?: "/run/systemd/cryptsetup";

        arg_disks = hashmap_new(&crypt_device_hash_ops);
        if (!arg_disks)
                return log_oom();

        r = proc_cmdline_parse(parse_proc_cmdline_item, NULL, PROC_CMDLINE_STRIP_RD_PREFIX);
        if (r < 0)
                return log_warning_errno(r, "Failed to parse kernel command line: %m");

        if (!arg_enabled)
                return 0;

        r = add_crypttab_devices();
        if (r < 0)
                return r;

        r = add_proc_cmdline_devices();
        if (r < 0)
                return r;

        return 0;
}