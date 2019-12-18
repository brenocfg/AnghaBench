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
 void* atoi (char*) ; 
 int bsize ; 
 int count ; 
 scalar_t__ errflag ; 
 char* filename ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fsize ; 
 int getopt (int,char**,char*) ; 
 void* offset ; 
 int /*<<< orphan*/  rflag ; 
 int seed ; 
 int /*<<< orphan*/  srandom (int) ; 
 int /*<<< orphan*/  stderr ; 
 int time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage (char*) ; 
 scalar_t__ vflag ; 

__attribute__((used)) static void
parse_options(int argc, char *argv[])
{
	int c;

	extern char *optarg;
	extern int optind, optopt;

	count = fsize / bsize;
	seed = time(NULL);
	while ((c = getopt(argc, argv, "b:c:f:o:rs:v")) != -1) {
		switch (c) {
			case 'b':
				bsize = atoi(optarg);
				break;

			case 'c':
				count = atoi(optarg);
				break;

			case 'f':
				fsize = atoi(optarg);
				break;

			case 'o':
				offset = atoi(optarg);
				break;

			case 'r':
				rflag++;
				break;

			case 's':
				seed = atoi(optarg);
				break;

			case 'v':
				vflag++;
				break;

			case ':':
				(void) fprintf(stderr,
				    "Option -%c requires an operand\n", optopt);
				errflag++;
				break;

			case '?':
				(void) fprintf(stderr,
				    "Unrecognized option: -%c\n", optopt);
				errflag++;
				break;
		}

		if (errflag) {
			(void) usage(argv[0]);
		}
	}
	if (argc <= optind) {
		(void) fprintf(stderr,
		    "No filename specified\n");
		usage(argv[0]);
	}
	filename = argv[optind];

	if (vflag) {
		(void) fprintf(stderr, "Seed = %d\n", seed);
	}
	srandom(seed);
}