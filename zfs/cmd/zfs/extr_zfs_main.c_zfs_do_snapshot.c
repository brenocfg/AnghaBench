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
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_3__ {char* sd_snapname; int /*<<< orphan*/ * sd_nvl; void* sd_recursive; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ snap_cbdata_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  void* boolean_t ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int ZFS_TYPE_VOLUME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  nomem () ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  parseprop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  usage (void*) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ zfs_snapshot_cb (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int zfs_snapshot_nvl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_do_snapshot(int argc, char **argv)
{
	int ret = 0;
	int c;
	nvlist_t *props;
	snap_cbdata_t sd = { 0 };
	boolean_t multiple_snaps = B_FALSE;

	if (nvlist_alloc(&props, NV_UNIQUE_NAME, 0) != 0)
		nomem();
	if (nvlist_alloc(&sd.sd_nvl, NV_UNIQUE_NAME, 0) != 0)
		nomem();

	/* check options */
	while ((c = getopt(argc, argv, "ro:")) != -1) {
		switch (c) {
		case 'o':
			if (!parseprop(props, optarg)) {
				nvlist_free(sd.sd_nvl);
				nvlist_free(props);
				return (1);
			}
			break;
		case 'r':
			sd.sd_recursive = B_TRUE;
			multiple_snaps = B_TRUE;
			break;
		case '?':
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			goto usage;
		}
	}

	argc -= optind;
	argv += optind;

	/* check number of arguments */
	if (argc < 1) {
		(void) fprintf(stderr, gettext("missing snapshot argument\n"));
		goto usage;
	}

	if (argc > 1)
		multiple_snaps = B_TRUE;
	for (; argc > 0; argc--, argv++) {
		char *atp;
		zfs_handle_t *zhp;

		atp = strchr(argv[0], '@');
		if (atp == NULL)
			goto usage;
		*atp = '\0';
		sd.sd_snapname = atp + 1;
		zhp = zfs_open(g_zfs, argv[0],
		    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME);
		if (zhp == NULL)
			goto usage;
		if (zfs_snapshot_cb(zhp, &sd) != 0)
			goto usage;
	}

	ret = zfs_snapshot_nvl(g_zfs, sd.sd_nvl, props);
	nvlist_free(sd.sd_nvl);
	nvlist_free(props);
	if (ret != 0 && multiple_snaps)
		(void) fprintf(stderr, gettext("no snapshots were created\n"));
	return (ret != 0);

usage:
	nvlist_free(sd.sd_nvl);
	nvlist_free(props);
	usage(B_FALSE);
	return (-1);
}