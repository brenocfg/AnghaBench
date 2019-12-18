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
struct option {char* member_0; char member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  const member_1; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int) ; 
 char* arg_command ; 
 char* arg_syspath ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int getopt_long (int,char**,char*,struct option const*,int /*<<< orphan*/ *) ; 
 int help () ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 
#define  no_argument 128 
 int /*<<< orphan*/  optind ; 
 int print_version () ; 

__attribute__((used)) static int parse_argv(int argc, char *argv[]) {
        static const struct option options[] = {
                { "version", no_argument, NULL, 'V' },
                { "help",    no_argument, NULL, 'h' },
                {}
        };

        int c;

        while ((c = getopt_long(argc, argv, "Vh", options, NULL)) >= 0)
                switch (c) {
                case 'V':
                        return print_version();
                case 'h':
                        return help();
                case '?':
                        return -EINVAL;
                default:
                        assert_not_reached("Unknown option");
                }

        arg_command = argv[optind++];
        if (!arg_command)
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "Command missing.");

        arg_syspath = argv[optind++];
        if (!arg_syspath)
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "syspath missing.");

        return 1;
}