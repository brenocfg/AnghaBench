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
 int /*<<< orphan*/  OPT_STRING ; 
 int /*<<< orphan*/  PRINT_FATAL (char*,int /*<<< orphan*/ ) ; 
 char* TINI_VERSION_STRING ; 
 int /*<<< orphan*/  add_expect_status (int /*<<< orphan*/ ) ; 
 char*** calloc (int const,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getopt (int const,char* const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_process_group ; 
 int /*<<< orphan*/  optarg ; 
 int const optind ; 
 int /*<<< orphan*/  print_license (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_usage (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pdeathsig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char* const) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subreaper ; 
 int /*<<< orphan*/  verbosity ; 
 int /*<<< orphan*/  warn_on_reap ; 

int parse_args(const int argc, char* const argv[], char* (**child_args_ptr_ptr)[], int* const parse_fail_exitcode_ptr) {
	char* name = argv[0];

	// We handle --version if it's the *only* argument provided.
	if (argc == 2 && strcmp("--version", argv[1]) == 0) {
		*parse_fail_exitcode_ptr = 0;
		fprintf(stdout, "%s\n", TINI_VERSION_STRING);
		return 1;
	}

#ifndef TINI_MINIMAL
	int c;
	while ((c = getopt(argc, argv, OPT_STRING)) != -1) {
		switch (c) {
			case 'h':
				print_usage(name, stdout);
				*parse_fail_exitcode_ptr = 0;
				return 1;
#if HAS_SUBREAPER
			case 's':
				subreaper++;
				break;
#endif
			case 'p':
				if (set_pdeathsig(optarg)) {
					PRINT_FATAL("Not a valid option for -p: %s", optarg);
					*parse_fail_exitcode_ptr = 1;
					return 1;
				}
				break;

			case 'v':
				verbosity++;
				break;

			case 'w':
				warn_on_reap++;
				break;

			case 'g':
				kill_process_group++;
				break;

			case 'e':
				if (add_expect_status(optarg)) {
					PRINT_FATAL("Not a valid option for -e: %s", optarg);
					*parse_fail_exitcode_ptr = 1;
					return 1;
				}
				break;

			case 'l':
				print_license(stdout);
				*parse_fail_exitcode_ptr = 0;
				return 1;

			case '?':
				print_usage(name, stderr);
				return 1;
			default:
				/* Should never happen */
				return 1;
		}
	}
#endif

	*child_args_ptr_ptr = calloc(argc-optind+1, sizeof(char*));
	if (*child_args_ptr_ptr == NULL) {
		PRINT_FATAL("Failed to allocate memory for child args: '%s'", strerror(errno));
		return 1;
	}

	int i;
	for (i = 0; i < argc - optind; i++) {
		(**child_args_ptr_ptr)[i] = argv[optind+i];
	}
	(**child_args_ptr_ptr)[i] = NULL;

	if (i == 0) {
		/* User forgot to provide args! */
		print_usage(name, stderr);
		return 1;
	}

	return 0;
}