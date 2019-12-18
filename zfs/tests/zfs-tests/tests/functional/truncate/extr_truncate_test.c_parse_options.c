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
 int /*<<< orphan*/  atoi (char*) ; 
 scalar_t__ errflag ; 
 char* filename ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fsize ; 
 int /*<<< orphan*/  ftruncflag ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (char*) ; 

__attribute__((used)) static void
parse_options(int argc, char *argv[])
{
	int c;
	extern char *optarg;
	extern int optind, optopt;

	while ((c = getopt(argc, argv, "s:f")) != -1) {
		switch (c) {
			case 's':
				fsize = atoi(optarg);
				break;
			case 'f':
				ftruncflag++;
				break;
			case ':':
				(void) fprintf(stderr,
				    "Option -%c requires an operand\n", optopt);
				errflag++;
				break;
		}
		if (errflag) {
			(void) usage(argv[0]);
		}
	}

	if (argc <= optind) {
		(void) fprintf(stderr, "No filename specified\n");
		usage(argv[0]);
	}
	filename = argv[optind];
}