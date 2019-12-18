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
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  stderr ; 
 float strtof (char*,char**) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_isnumber (char*) ; 

__attribute__((used)) static void
get_interval_count(int *argcp, char **argv, float *iv,
    unsigned long *cnt)
{
	float interval = 0;
	unsigned long count = 0;
	int argc = *argcp;

	/*
	 * Determine if the last argument is an integer or a pool name
	 */
	if (argc > 0 && zfs_isnumber(argv[argc - 1])) {
		char *end;

		errno = 0;
		interval = strtof(argv[argc - 1], &end);

		if (*end == '\0' && errno == 0) {
			if (interval == 0) {
				(void) fprintf(stderr, gettext("interval "
				    "cannot be zero\n"));
				usage(B_FALSE);
			}
			/*
			 * Ignore the last parameter
			 */
			argc--;
		} else {
			/*
			 * If this is not a valid number, just plow on.  The
			 * user will get a more informative error message later
			 * on.
			 */
			interval = 0;
		}
	}

	/*
	 * If the last argument is also an integer, then we have both a count
	 * and an interval.
	 */
	if (argc > 0 && zfs_isnumber(argv[argc - 1])) {
		char *end;

		errno = 0;
		count = interval;
		interval = strtof(argv[argc - 1], &end);

		if (*end == '\0' && errno == 0) {
			if (interval == 0) {
				(void) fprintf(stderr, gettext("interval "
				    "cannot be zero\n"));
				usage(B_FALSE);
			}

			/*
			 * Ignore the last parameter
			 */
			argc--;
		} else {
			interval = 0;
		}
	}

	*iv = interval;
	*cnt = count;
	*argcp = argc;
}