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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  ZPOOL_DO_REWIND ; 
 int /*<<< orphan*/  ZPOOL_EXTREME_REWIND ; 
 int /*<<< orphan*/  ZPOOL_LOAD_REWIND_POLICY ; 
 int /*<<< orphan*/  ZPOOL_NO_REWIND ; 
 int /*<<< orphan*/  ZPOOL_TRY_REWIND ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 scalar_t__ nvlist_add_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (scalar_t__) ; 
 scalar_t__ zpool_clear (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_open_canfail (int /*<<< orphan*/ ,char*) ; 

int
zpool_do_clear(int argc, char **argv)
{
	int c;
	int ret = 0;
	boolean_t dryrun = B_FALSE;
	boolean_t do_rewind = B_FALSE;
	boolean_t xtreme_rewind = B_FALSE;
	uint32_t rewind_policy = ZPOOL_NO_REWIND;
	nvlist_t *policy = NULL;
	zpool_handle_t *zhp;
	char *pool, *device;

	/* check options */
	while ((c = getopt(argc, argv, "FnX")) != -1) {
		switch (c) {
		case 'F':
			do_rewind = B_TRUE;
			break;
		case 'n':
			dryrun = B_TRUE;
			break;
		case 'X':
			xtreme_rewind = B_TRUE;
			break;
		case '?':
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			usage(B_FALSE);
		}
	}

	argc -= optind;
	argv += optind;

	if (argc < 1) {
		(void) fprintf(stderr, gettext("missing pool name\n"));
		usage(B_FALSE);
	}

	if (argc > 2) {
		(void) fprintf(stderr, gettext("too many arguments\n"));
		usage(B_FALSE);
	}

	if ((dryrun || xtreme_rewind) && !do_rewind) {
		(void) fprintf(stderr,
		    gettext("-n or -X only meaningful with -F\n"));
		usage(B_FALSE);
	}
	if (dryrun)
		rewind_policy = ZPOOL_TRY_REWIND;
	else if (do_rewind)
		rewind_policy = ZPOOL_DO_REWIND;
	if (xtreme_rewind)
		rewind_policy |= ZPOOL_EXTREME_REWIND;

	/* In future, further rewind policy choices can be passed along here */
	if (nvlist_alloc(&policy, NV_UNIQUE_NAME, 0) != 0 ||
	    nvlist_add_uint32(policy, ZPOOL_LOAD_REWIND_POLICY,
	    rewind_policy) != 0) {
		return (1);
	}

	pool = argv[0];
	device = argc == 2 ? argv[1] : NULL;

	if ((zhp = zpool_open_canfail(g_zfs, pool)) == NULL) {
		nvlist_free(policy);
		return (1);
	}

	if (zpool_clear(zhp, device, policy) != 0)
		ret = 1;

	zpool_close(zhp);

	nvlist_free(policy);

	return (ret);
}