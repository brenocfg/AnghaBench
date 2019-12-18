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
 int ZFS_ITER_DEPTH_LIMIT ; 
 int ZFS_ITER_RECURSE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* gettext (char*) ; 
 char* optarg ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_depth(char *opt, int *flags)
{
	char *tmp;
	int depth;

	depth = (int)strtol(opt, &tmp, 0);
	if (*tmp) {
		(void) fprintf(stderr,
		    gettext("%s is not an integer\n"), optarg);
		usage(B_FALSE);
	}
	if (depth < 0) {
		(void) fprintf(stderr,
		    gettext("Depth can not be negative.\n"));
		usage(B_FALSE);
	}
	*flags |= (ZFS_ITER_DEPTH_LIMIT|ZFS_ITER_RECURSE);
	return (depth);
}