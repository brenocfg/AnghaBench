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
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 char* GIT_VERSION ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_TARGET_CONSOLE ; 
 int /*<<< orphan*/  MAX_PATH_LEN ; 
 int /*<<< orphan*/  PAGE_80 ; 
 int /*<<< orphan*/  PAGE_83 ; 
 int /*<<< orphan*/  PAGE_83_PRE_SPC3 ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int all_good ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int atoi (char*) ; 
 char* config_file ; 
 int /*<<< orphan*/  default_page_code ; 
 int dev_specified ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int export ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  help () ; 
 int log_error_errno (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_set_max_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_set_target (int /*<<< orphan*/ ) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int reformat_serial ; 
 int sg_version ; 
 int /*<<< orphan*/  streq (char*,char*) ; 
 int /*<<< orphan*/  strscpy (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int set_options(int argc, char **argv,
                       char *maj_min_dev) {
        int option;

        /*
         * optind is a global extern used by getopt. Since we can call
         * set_options twice (once for command line, and once for config
         * file) we have to reset this back to 1.
         */
        optind = 1;
        while ((option = getopt_long(argc, argv, "d:f:gp:uvVxhbs:", options, NULL)) >= 0)
                switch (option) {
                case 'b':
                        all_good = false;
                        break;

                case 'd':
                        dev_specified = true;
                        strscpy(maj_min_dev, MAX_PATH_LEN, optarg);
                        break;

                case 'f':
                        strscpy(config_file, MAX_PATH_LEN, optarg);
                        break;

                case 'g':
                        all_good = true;
                        break;

                case 'h':
                        help();
                        exit(EXIT_SUCCESS);

                case 'p':
                        if (streq(optarg, "0x80"))
                                default_page_code = PAGE_80;
                        else if (streq(optarg, "0x83"))
                                default_page_code = PAGE_83;
                        else if (streq(optarg, "pre-spc3-83"))
                                default_page_code = PAGE_83_PRE_SPC3;
                        else
                                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                                       "Unknown page code '%s'",
                                                       optarg);
                        break;

                case 's':
                        sg_version = atoi(optarg);
                        if (sg_version < 3 || sg_version > 4)
                                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                                       "Unknown SG version '%s'",
                                                       optarg);
                        break;

                case 'u':
                        reformat_serial = true;
                        break;

                case 'v':
                        log_set_target(LOG_TARGET_CONSOLE);
                        log_set_max_level(LOG_DEBUG);
                        log_open();
                        break;

                case 'V':
                        printf("%s\n", GIT_VERSION);
                        exit(EXIT_SUCCESS);

                case 'x':
                        export = true;
                        break;

                case '?':
                        return -1;

                default:
                        assert_not_reached("Unknown option");
                }

        if (optind < argc && !dev_specified) {
                dev_specified = true;
                strscpy(maj_min_dev, MAX_PATH_LEN, argv[optind]);
        }

        return 0;
}