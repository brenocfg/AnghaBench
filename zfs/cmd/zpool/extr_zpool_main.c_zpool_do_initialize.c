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
typedef  scalar_t__ pool_initialize_func_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 scalar_t__ POOL_INITIALIZE_CANCEL ; 
 scalar_t__ POOL_INITIALIZE_START ; 
 scalar_t__ POOL_INITIALIZE_SUSPEND ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt_long (int,char**,char*,struct option*,int /*<<< orphan*/ *) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  no_argument ; 
 size_t optind ; 
 int optopt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (scalar_t__) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_collect_leaves (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zpool_initialize (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int zpool_initialize_wait (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_open (int /*<<< orphan*/ ,char*) ; 

int
zpool_do_initialize(int argc, char **argv)
{
	int c;
	char *poolname;
	zpool_handle_t *zhp;
	nvlist_t *vdevs;
	int err = 0;
	boolean_t wait = B_FALSE;

	struct option long_options[] = {
		{"cancel",	no_argument,		NULL, 'c'},
		{"suspend",	no_argument,		NULL, 's'},
		{"wait",	no_argument,		NULL, 'w'},
		{0, 0, 0, 0}
	};

	pool_initialize_func_t cmd_type = POOL_INITIALIZE_START;
	while ((c = getopt_long(argc, argv, "csw", long_options, NULL)) != -1) {
		switch (c) {
		case 'c':
			if (cmd_type != POOL_INITIALIZE_START &&
			    cmd_type != POOL_INITIALIZE_CANCEL) {
				(void) fprintf(stderr, gettext("-c cannot be "
				    "combined with other options\n"));
				usage(B_FALSE);
			}
			cmd_type = POOL_INITIALIZE_CANCEL;
			break;
		case 's':
			if (cmd_type != POOL_INITIALIZE_START &&
			    cmd_type != POOL_INITIALIZE_SUSPEND) {
				(void) fprintf(stderr, gettext("-s cannot be "
				    "combined with other options\n"));
				usage(B_FALSE);
			}
			cmd_type = POOL_INITIALIZE_SUSPEND;
			break;
		case 'w':
			wait = B_TRUE;
			break;
		case '?':
			if (optopt != 0) {
				(void) fprintf(stderr,
				    gettext("invalid option '%c'\n"), optopt);
			} else {
				(void) fprintf(stderr,
				    gettext("invalid option '%s'\n"),
				    argv[optind - 1]);
			}
			usage(B_FALSE);
		}
	}

	argc -= optind;
	argv += optind;

	if (argc < 1) {
		(void) fprintf(stderr, gettext("missing pool name argument\n"));
		usage(B_FALSE);
		return (-1);
	}

	if (wait && (cmd_type != POOL_INITIALIZE_START)) {
		(void) fprintf(stderr, gettext("-w cannot be used with -c or "
		    "-s\n"));
		usage(B_FALSE);
	}

	poolname = argv[0];
	zhp = zpool_open(g_zfs, poolname);
	if (zhp == NULL)
		return (-1);

	vdevs = fnvlist_alloc();
	if (argc == 1) {
		/* no individual leaf vdevs specified, so add them all */
		nvlist_t *config = zpool_get_config(zhp, NULL);
		nvlist_t *nvroot = fnvlist_lookup_nvlist(config,
		    ZPOOL_CONFIG_VDEV_TREE);
		zpool_collect_leaves(zhp, nvroot, vdevs);
	} else {
		for (int i = 1; i < argc; i++) {
			fnvlist_add_boolean(vdevs, argv[i]);
		}
	}

	if (wait)
		err = zpool_initialize_wait(zhp, cmd_type, vdevs);
	else
		err = zpool_initialize(zhp, cmd_type, vdevs);

	fnvlist_free(vdevs);
	zpool_close(zhp);

	return (err);
}