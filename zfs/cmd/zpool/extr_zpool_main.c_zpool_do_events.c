#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int verbose; int scripted; int follow; int clear; char* poolname; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ev_opts_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  ZFS_TYPE_POOL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_name_valid (char*,int /*<<< orphan*/ ) ; 
 int zpool_do_events_clear (TYPE_1__*) ; 
 int zpool_do_events_next (TYPE_1__*) ; 

int
zpool_do_events(int argc, char **argv)
{
	ev_opts_t opts = { 0 };
	int ret;
	int c;

	/* check options */
	while ((c = getopt(argc, argv, "vHfc")) != -1) {
		switch (c) {
		case 'v':
			opts.verbose = 1;
			break;
		case 'H':
			opts.scripted = 1;
			break;
		case 'f':
			opts.follow = 1;
			break;
		case 'c':
			opts.clear = 1;
			break;
		case '?':
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			usage(B_FALSE);
		}
	}
	argc -= optind;
	argv += optind;

	if (argc > 1) {
		(void) fprintf(stderr, gettext("too many arguments\n"));
		usage(B_FALSE);
	} else if (argc == 1) {
		(void) strlcpy(opts.poolname, argv[0], sizeof (opts.poolname));
		if (!zfs_name_valid(opts.poolname, ZFS_TYPE_POOL)) {
			(void) fprintf(stderr,
			    gettext("invalid pool name '%s'\n"), opts.poolname);
			usage(B_FALSE);
		}
	}

	if ((argc == 1 || opts.verbose || opts.scripted || opts.follow) &&
	    opts.clear) {
		(void) fprintf(stderr,
		    gettext("invalid options combined with -c\n"));
		usage(B_FALSE);
	}

	if (opts.clear)
		ret = zpool_do_events_clear(&opts);
	else
		ret = zpool_do_events_next(&opts);

	return (ret);
}