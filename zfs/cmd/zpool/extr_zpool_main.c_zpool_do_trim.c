#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {void* fullpool; int /*<<< orphan*/  rate; void* secure; } ;
typedef  TYPE_1__ trimflags_t ;
struct option {char* member_0; char member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; } ;
typedef  int /*<<< orphan*/  pool_trim_func_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  void* boolean_t ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  POOL_TRIM_CANCEL ; 
 int /*<<< orphan*/  POOL_TRIM_START ; 
 int /*<<< orphan*/  POOL_TRIM_SUSPEND ; 
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
 int /*<<< orphan*/  optarg ; 
 size_t optind ; 
 int optopt ; 
 int /*<<< orphan*/  required_argument ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (void*) ; 
 int zfs_nicestrtonum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_collect_leaves (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_open (int /*<<< orphan*/ ,char*) ; 
 int zpool_trim (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

int
zpool_do_trim(int argc, char **argv)
{
	struct option long_options[] = {
		{"cancel",	no_argument,		NULL,	'c'},
		{"secure",	no_argument,		NULL,	'd'},
		{"rate",	required_argument,	NULL,	'r'},
		{"suspend",	no_argument,		NULL,	's'},
		{0, 0, 0, 0}
	};

	pool_trim_func_t cmd_type = POOL_TRIM_START;
	uint64_t rate = 0;
	boolean_t secure = B_FALSE;

	int c;
	while ((c = getopt_long(argc, argv, "cdr:s", long_options, NULL))
	    != -1) {
		switch (c) {
		case 'c':
			if (cmd_type != POOL_TRIM_START &&
			    cmd_type != POOL_TRIM_CANCEL) {
				(void) fprintf(stderr, gettext("-c cannot be "
				    "combined with other options\n"));
				usage(B_FALSE);
			}
			cmd_type = POOL_TRIM_CANCEL;
			break;
		case 'd':
			if (cmd_type != POOL_TRIM_START) {
				(void) fprintf(stderr, gettext("-d cannot be "
				    "combined with the -c or -s options\n"));
				usage(B_FALSE);
			}
			secure = B_TRUE;
			break;
		case 'r':
			if (cmd_type != POOL_TRIM_START) {
				(void) fprintf(stderr, gettext("-r cannot be "
				    "combined with the -c or -s options\n"));
				usage(B_FALSE);
			}
			if (zfs_nicestrtonum(NULL, optarg, &rate) == -1) {
				(void) fprintf(stderr,
				    gettext("invalid value for rate\n"));
				usage(B_FALSE);
			}
			break;
		case 's':
			if (cmd_type != POOL_TRIM_START &&
			    cmd_type != POOL_TRIM_SUSPEND) {
				(void) fprintf(stderr, gettext("-s cannot be "
				    "combined with other options\n"));
				usage(B_FALSE);
			}
			cmd_type = POOL_TRIM_SUSPEND;
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

	char *poolname = argv[0];
	zpool_handle_t *zhp = zpool_open(g_zfs, poolname);
	if (zhp == NULL)
		return (-1);

	trimflags_t trim_flags = {
		.secure = secure,
		.rate = rate,
	};

	nvlist_t *vdevs = fnvlist_alloc();
	if (argc == 1) {
		/* no individual leaf vdevs specified, so add them all */
		nvlist_t *config = zpool_get_config(zhp, NULL);
		nvlist_t *nvroot = fnvlist_lookup_nvlist(config,
		    ZPOOL_CONFIG_VDEV_TREE);
		zpool_collect_leaves(zhp, nvroot, vdevs);
		trim_flags.fullpool = B_TRUE;
	} else {
		trim_flags.fullpool = B_FALSE;
		for (int i = 1; i < argc; i++) {
			fnvlist_add_boolean(vdevs, argv[i]);
		}
	}

	int error = zpool_trim(zhp, cmd_type, vdevs, &trim_flags);

	fnvlist_free(vdevs);
	zpool_close(zhp);

	return (error);
}