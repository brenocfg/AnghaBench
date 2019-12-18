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
 int SHOW_DEFAULTS ; 
 int SHOW_OVERRIDDEN ; 
 int arg_diff ; 
 int arg_flags ; 
 int /*<<< orphan*/  arg_pager_flags ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 int /*<<< orphan*/  log_show_color (int) ; 
 int optind ; 
 int /*<<< orphan*/  pager_open (int /*<<< orphan*/ ) ; 
 int parse_argv (int,char**) ; 
 int /*<<< orphan*/  path_simplify (char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int process_suffix_chop (char*) ; 
 int process_suffixes (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int run(int argc, char *argv[]) {
        int r, k, n_found = 0;

        log_show_color(true);
        log_parse_environment();
        log_open();

        r = parse_argv(argc, argv);
        if (r <= 0)
                return r;

        if (arg_flags == 0)
                arg_flags = SHOW_DEFAULTS;

        if (arg_diff < 0)
                arg_diff = !!(arg_flags & SHOW_OVERRIDDEN);
        else if (arg_diff)
                arg_flags |= SHOW_OVERRIDDEN;

        (void) pager_open(arg_pager_flags);

        if (optind < argc) {
                int i;

                for (i = optind; i < argc; i++) {
                        path_simplify(argv[i], false);

                        k = process_suffix_chop(argv[i]);
                        if (k < 0)
                                r = k;
                        else
                                n_found += k;
                }

        } else {
                k = process_suffixes(NULL);
                if (k < 0)
                        r = k;
                else
                        n_found += k;
        }

        if (r >= 0)
                printf("%s%i overridden configuration files found.\n", n_found ? "\n" : "", n_found);
        return r;
}