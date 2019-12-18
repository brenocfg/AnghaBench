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
struct TYPE_3__ {int cb_version; scalar_t__ cb_numfailed; void* cb_foundone; void* cb_newer; scalar_t__ cb_numsamegraded; scalar_t__ cb_numupgraded; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ upgrade_cbdata_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  void* boolean_t ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 int ZFS_ITER_ARGS_CAN_BE_PATHS ; 
 int ZFS_ITER_RECURSE ; 
 int /*<<< orphan*/  ZFS_PROP_VERSION ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int ZPL_VERSION ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  upgrade_list_callback ; 
 int /*<<< orphan*/  upgrade_set_callback ; 
 int /*<<< orphan*/  usage (void*) ; 
 int zfs_for_each (int,char**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_prop_string_to_index (int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int
zfs_do_upgrade(int argc, char **argv)
{
	boolean_t all = B_FALSE;
	boolean_t showversions = B_FALSE;
	int ret = 0;
	upgrade_cbdata_t cb = { 0 };
	int c;
	int flags = ZFS_ITER_ARGS_CAN_BE_PATHS;

	/* check options */
	while ((c = getopt(argc, argv, "rvV:a")) != -1) {
		switch (c) {
		case 'r':
			flags |= ZFS_ITER_RECURSE;
			break;
		case 'v':
			showversions = B_TRUE;
			break;
		case 'V':
			if (zfs_prop_string_to_index(ZFS_PROP_VERSION,
			    optarg, &cb.cb_version) != 0) {
				(void) fprintf(stderr,
				    gettext("invalid version %s\n"), optarg);
				usage(B_FALSE);
			}
			break;
		case 'a':
			all = B_TRUE;
			break;
		case '?':
		default:
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			usage(B_FALSE);
		}
	}

	argc -= optind;
	argv += optind;

	if ((!all && !argc) && ((flags & ZFS_ITER_RECURSE) | cb.cb_version))
		usage(B_FALSE);
	if (showversions && (flags & ZFS_ITER_RECURSE || all ||
	    cb.cb_version || argc))
		usage(B_FALSE);
	if ((all || argc) && (showversions))
		usage(B_FALSE);
	if (all && argc)
		usage(B_FALSE);

	if (showversions) {
		/* Show info on available versions. */
		(void) printf(gettext("The following filesystem versions are "
		    "supported:\n\n"));
		(void) printf(gettext("VER  DESCRIPTION\n"));
		(void) printf("---  -----------------------------------------"
		    "---------------\n");
		(void) printf(gettext(" 1   Initial ZFS filesystem version\n"));
		(void) printf(gettext(" 2   Enhanced directory entries\n"));
		(void) printf(gettext(" 3   Case insensitive and filesystem "
		    "user identifier (FUID)\n"));
		(void) printf(gettext(" 4   userquota, groupquota "
		    "properties\n"));
		(void) printf(gettext(" 5   System attributes\n"));
		(void) printf(gettext("\nFor more information on a particular "
		    "version, including supported releases,\n"));
		(void) printf("see the ZFS Administration Guide.\n\n");
		ret = 0;
	} else if (argc || all) {
		/* Upgrade filesystems */
		if (cb.cb_version == 0)
			cb.cb_version = ZPL_VERSION;
		ret = zfs_for_each(argc, argv, flags, ZFS_TYPE_FILESYSTEM,
		    NULL, NULL, 0, upgrade_set_callback, &cb);
		(void) printf(gettext("%llu filesystems upgraded\n"),
		    (u_longlong_t)cb.cb_numupgraded);
		if (cb.cb_numsamegraded) {
			(void) printf(gettext("%llu filesystems already at "
			    "this version\n"),
			    (u_longlong_t)cb.cb_numsamegraded);
		}
		if (cb.cb_numfailed != 0)
			ret = 1;
	} else {
		/* List old-version filesystems */
		boolean_t found;
		(void) printf(gettext("This system is currently running "
		    "ZFS filesystem version %llu.\n\n"), ZPL_VERSION);

		flags |= ZFS_ITER_RECURSE;
		ret = zfs_for_each(0, NULL, flags, ZFS_TYPE_FILESYSTEM,
		    NULL, NULL, 0, upgrade_list_callback, &cb);

		found = cb.cb_foundone;
		cb.cb_foundone = B_FALSE;
		cb.cb_newer = B_TRUE;

		ret = zfs_for_each(0, NULL, flags, ZFS_TYPE_FILESYSTEM,
		    NULL, NULL, 0, upgrade_list_callback, &cb);

		if (!cb.cb_foundone && !found) {
			(void) printf(gettext("All filesystems are "
			    "formatted with the current version.\n"));
		}
	}

	return (ret);
}