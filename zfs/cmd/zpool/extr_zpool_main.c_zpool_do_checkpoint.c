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
struct option {char* member_0; char member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  ZPOOL_WAIT_CKPT_DISCARD ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt_long (int,char**,char*,struct option*,int /*<<< orphan*/ *) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  no_argument ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  usage (scalar_t__) ; 
 scalar_t__ zpool_checkpoint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_discard_checkpoint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_open (int /*<<< orphan*/ ,char*) ; 
 int zpool_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
zpool_do_checkpoint(int argc, char **argv)
{
	boolean_t discard, wait;
	char *pool;
	zpool_handle_t *zhp;
	int c, err;

	struct option long_options[] = {
		{"discard", no_argument, NULL, 'd'},
		{"wait", no_argument, NULL, 'w'},
		{0, 0, 0, 0}
	};

	discard = B_FALSE;
	wait = B_FALSE;
	while ((c = getopt_long(argc, argv, ":dw", long_options, NULL)) != -1) {
		switch (c) {
		case 'd':
			discard = B_TRUE;
			break;
		case 'w':
			wait = B_TRUE;
			break;
		case '?':
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			usage(B_FALSE);
		}
	}

	if (wait && !discard) {
		(void) fprintf(stderr, gettext("--wait only valid when "
		    "--discard also specified\n"));
		usage(B_FALSE);
	}

	argc -= optind;
	argv += optind;

	if (argc < 1) {
		(void) fprintf(stderr, gettext("missing pool argument\n"));
		usage(B_FALSE);
	}

	if (argc > 1) {
		(void) fprintf(stderr, gettext("too many arguments\n"));
		usage(B_FALSE);
	}

	pool = argv[0];

	if ((zhp = zpool_open(g_zfs, pool)) == NULL) {
		/* As a special case, check for use of '/' in the name */
		if (strchr(pool, '/') != NULL)
			(void) fprintf(stderr, gettext("'zpool checkpoint' "
			    "doesn't work on datasets. To save the state "
			    "of a dataset from a specific point in time "
			    "please use 'zfs snapshot'\n"));
		return (1);
	}

	if (discard) {
		err = (zpool_discard_checkpoint(zhp) != 0);
		if (err == 0 && wait)
			err = zpool_wait(zhp, ZPOOL_WAIT_CKPT_DISCARD);
	} else {
		err = (zpool_checkpoint(zhp) != 0);
	}

	zpool_close(zhp);

	return (err);
}