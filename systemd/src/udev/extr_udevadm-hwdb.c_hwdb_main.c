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
 int /*<<< orphan*/  arg_hwdb_bin_dir ; 
 int /*<<< orphan*/  arg_root ; 
 int /*<<< orphan*/  arg_strict ; 
 scalar_t__ arg_test ; 
 scalar_t__ arg_update ; 
 int hwdb_query (scalar_t__) ; 
 int hwdb_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 
 int parse_argv (int,char**) ; 

int hwdb_main(int argc, char *argv[], void *userdata) {
        int r;

        r = parse_argv(argc, argv);
        if (r <= 0)
                return r;

        if (!arg_update && !arg_test)
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "Either --update or --test must be used.");

        if (arg_update) {
                r = hwdb_update(arg_root, arg_hwdb_bin_dir, arg_strict, true);
                if (r < 0)
                        return r;
        }

        if (arg_test)
                return hwdb_query(arg_test);

        return 0;
}