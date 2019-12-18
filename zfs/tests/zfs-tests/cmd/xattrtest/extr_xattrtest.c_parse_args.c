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
 int /*<<< orphan*/  PATH_MAX ; 
 int PHASE_ALL ; 
 int PHASE_INVAL ; 
 int XATTR_SIZE_MAX ; 
 int dropcaches ; 
 int files ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt_long (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int keep_files ; 
 int /*<<< orphan*/  longopts ; 
 int nth ; 
 int /*<<< orphan*/  optarg ; 
 char* path ; 
 int phase ; 
 char* script ; 
 int /*<<< orphan*/  shortopts ; 
 int size ; 
 int size_is_random ; 
 int /*<<< orphan*/  srandom (long) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int synccaches ; 
 long time (int /*<<< orphan*/ *) ; 
 int usage (int,char**) ; 
 int value_is_random ; 
 int verbose ; 
 int verify ; 
 int xattrs ; 

__attribute__((used)) static int
parse_args(int argc, char **argv)
{
	long seed = time(NULL);
	int c;
	int rc = 0;

	while ((c = getopt_long(argc, argv, shortopts, longopts, NULL)) != -1) {
		switch (c) {
		case 'h':
			return (usage(argc, argv));
		case 'v':
			verbose++;
			break;
		case 'y':
			verify = 1;
			break;
		case 'n':
			nth = strtol(optarg, NULL, 0);
			break;
		case 'f':
			files = strtol(optarg, NULL, 0);
			break;
		case 'x':
			xattrs = strtol(optarg, NULL, 0);
			break;
		case 's':
			size = strtol(optarg, NULL, 0);
			if (size > XATTR_SIZE_MAX) {
				fprintf(stderr, "Error: the -s value may not "
				    "be greater than %d\n", XATTR_SIZE_MAX);
				rc = 1;
			}
			break;
		case 'p':
			strncpy(path, optarg, PATH_MAX);
			path[PATH_MAX - 1] = '\0';
			break;
		case 'c':
			synccaches = 1;
			break;
		case 'd':
			dropcaches = 1;
			break;
		case 't':
			strncpy(script, optarg, PATH_MAX);
			script[PATH_MAX - 1] = '\0';
			break;
		case 'e':
			seed = strtol(optarg, NULL, 0);
			break;
		case 'r':
			size_is_random = 1;
			break;
		case 'R':
			value_is_random = 1;
			break;
		case 'k':
			keep_files = 1;
			break;
		case 'o':
			phase = strtol(optarg, NULL, 0);
			if (phase <= PHASE_ALL || phase >= PHASE_INVAL) {
				fprintf(stderr, "Error: the -o value must be "
				    "greater than %d and less than %d\n",
				    PHASE_ALL, PHASE_INVAL);
				rc = 1;
			}
			break;
		default:
			rc = 1;
			break;
		}
	}

	if (rc != 0)
		return (rc);

	srandom(seed);

	if (verbose) {
		fprintf(stdout, "verbose:          %d\n", verbose);
		fprintf(stdout, "verify:           %d\n", verify);
		fprintf(stdout, "nth:              %d\n", nth);
		fprintf(stdout, "files:            %d\n", files);
		fprintf(stdout, "xattrs:           %d\n", xattrs);
		fprintf(stdout, "size:             %d\n", size);
		fprintf(stdout, "path:             %s\n", path);
		fprintf(stdout, "synccaches:       %d\n", synccaches);
		fprintf(stdout, "dropcaches:       %d\n", dropcaches);
		fprintf(stdout, "script:           %s\n", script);
		fprintf(stdout, "seed:             %ld\n", seed);
		fprintf(stdout, "random size:      %d\n", size_is_random);
		fprintf(stdout, "random value:     %d\n", value_is_random);
		fprintf(stdout, "keep:             %d\n", keep_files);
		fprintf(stdout, "only:             %d\n", phase);
		fprintf(stdout, "%s", "\n");
	}

	return (rc);
}