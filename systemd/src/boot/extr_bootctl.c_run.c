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
 int arg_touch_variables ; 
 int bootctl_main (int,char**) ; 
 scalar_t__ detect_container () ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 int parse_argv (int,char**) ; 

__attribute__((used)) static int run(int argc, char *argv[]) {
        int r;

        log_parse_environment();
        log_open();

        /* If we run in a container, automatically turn off EFI file system access */
        if (detect_container() > 0)
                arg_touch_variables = false;

        r = parse_argv(argc, argv);
        if (r <= 0)
                return r;

        return bootctl_main(argc, argv);
}