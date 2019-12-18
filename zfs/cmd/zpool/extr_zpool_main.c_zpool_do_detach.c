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
typedef  int /*<<< orphan*/  zpool_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_open (int /*<<< orphan*/ ,char*) ; 
 int zpool_vdev_detach (int /*<<< orphan*/ *,char*) ; 

int
zpool_do_detach(int argc, char **argv)
{
	int c;
	char *poolname, *path;
	zpool_handle_t *zhp;
	int ret;

	/* check options */
	while ((c = getopt(argc, argv, "")) != -1) {
		switch (c) {
		case '?':
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			usage(B_FALSE);
		}
	}

	argc -= optind;
	argv += optind;

	/* get pool name and check number of arguments */
	if (argc < 1) {
		(void) fprintf(stderr, gettext("missing pool name argument\n"));
		usage(B_FALSE);
	}

	if (argc < 2) {
		(void) fprintf(stderr,
		    gettext("missing <device> specification\n"));
		usage(B_FALSE);
	}

	poolname = argv[0];
	path = argv[1];

	if ((zhp = zpool_open(g_zfs, poolname)) == NULL)
		return (1);

	ret = zpool_vdev_detach(zhp, path);

	zpool_close(zhp);

	return (ret);
}