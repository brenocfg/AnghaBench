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
typedef  int /*<<< orphan*/  sd_id128_t ;

/* Variables and functions */
 int /*<<< orphan*/  ID128_PLAIN ; 
 int /*<<< orphan*/  SD_ID128_NULL ; 
 int SD_ID128_STRING_MAX ; 
 scalar_t__ arg_commit ; 
 scalar_t__ arg_print ; 
 int /*<<< orphan*/  arg_root ; 
 int id128_read (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 int machine_id_commit (int /*<<< orphan*/ ) ; 
 int machine_id_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int parse_argv (int,char**) ; 
 char* prefix_roota (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_id128_to_string (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int run(int argc, char *argv[]) {
        char buf[SD_ID128_STRING_MAX];
        sd_id128_t id;
        int r;

        log_parse_environment();
        log_open();

        r = parse_argv(argc, argv);
        if (r <= 0)
                return r;

        if (arg_commit) {
                const char *etc_machine_id;

                r = machine_id_commit(arg_root);
                if (r < 0)
                        return r;

                etc_machine_id = prefix_roota(arg_root, "/etc/machine-id");
                r = id128_read(etc_machine_id, ID128_PLAIN, &id);
                if (r < 0)
                        return log_error_errno(r, "Failed to read machine ID back: %m");
        } else {
                r = machine_id_setup(arg_root, SD_ID128_NULL, &id);
                if (r < 0)
                        return r;
        }

        if (arg_print)
                puts(sd_id128_to_string(id, buf));

        return 0;
}