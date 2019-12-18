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
 int list_homes () ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 int /*<<< orphan*/  log_show_color (int) ; 
 int optind ; 
 int parse_argv (int,char**) ; 
 int print_home (char*) ; 

__attribute__((used)) static int run(int argc, char* argv[]) {
        int r;

        log_show_color(true);
        log_parse_environment();
        log_open();

        r = parse_argv(argc, argv);
        if (r <= 0)
                return r;

        if (argc > optind) {
                int i, q;

                for (i = optind; i < argc; i++) {
                        q = print_home(argv[i]);
                        if (q < 0)
                                r = q;
                }

                return r;
        } else
                return list_homes();
}