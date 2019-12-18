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
 char* GIT_VERSION ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int arg_monitor ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int getopt_long (int,char**,char*,struct option const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_set_max_level (int /*<<< orphan*/ ) ; 
#define  no_argument 129 
 char* optarg ; 
 int /*<<< orphan*/  printf (char*,...) ; 
#define  required_argument 128 

__attribute__((used)) static int parse_args(int argc, char *argv[], const char **syspath, const char **subsystem) {
        static const struct option options[] = {
                { "syspath",   required_argument, NULL, 'p' },
                { "subsystem", required_argument, NULL, 's' },
                { "debug",     no_argument,       NULL, 'd' },
                { "help",      no_argument,       NULL, 'h' },
                { "version",   no_argument,       NULL, 'V' },
                { "monitor",   no_argument,       NULL, 'm' },
                {}
        };
        int c;

        while ((c = getopt_long(argc, argv, "p:s:dhVm", options, NULL)) >= 0)
                switch (c) {
                case 'p':
                        *syspath = optarg;
                        break;

                case 's':
                        *subsystem = optarg;
                        break;

                case 'd':
                        log_set_max_level(LOG_DEBUG);
                        break;

                case 'h':
                        printf("--debug --syspath= --subsystem= --help\n");
                        return 0;

                case 'V':
                        printf("%s\n", GIT_VERSION);
                        return 0;

                case 'm':
                        arg_monitor = true;
                        break;

                case '?':
                        return -EINVAL;

                default:
                        assert_not_reached("Unhandled option code.");
                }

        return 1;
}