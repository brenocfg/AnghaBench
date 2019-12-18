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
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {int cb_recurse; int cb_doclones; char* cb_target; scalar_t__ cb_create; int cb_error; void* cb_first; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ rollback_cbdata_t ;
typedef  int /*<<< orphan*/  parentname ;
typedef  void* boolean_t ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_CREATETXG ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  rollback_check ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  usage (void*) ; 
 int /*<<< orphan*/  verify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int zfs_iter_bookmarks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int zfs_iter_snapshots (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zfs_rollback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int
zfs_do_rollback(int argc, char **argv)
{
	int ret = 0;
	int c;
	boolean_t force = B_FALSE;
	rollback_cbdata_t cb = { 0 };
	zfs_handle_t *zhp, *snap;
	char parentname[ZFS_MAX_DATASET_NAME_LEN];
	char *delim;
	uint64_t min_txg = 0;

	/* check options */
	while ((c = getopt(argc, argv, "rRf")) != -1) {
		switch (c) {
		case 'r':
			cb.cb_recurse = 1;
			break;
		case 'R':
			cb.cb_recurse = 1;
			cb.cb_doclones = 1;
			break;
		case 'f':
			force = B_TRUE;
			break;
		case '?':
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			usage(B_FALSE);
		}
	}

	argc -= optind;
	argv += optind;

	/* check number of arguments */
	if (argc < 1) {
		(void) fprintf(stderr, gettext("missing dataset argument\n"));
		usage(B_FALSE);
	}
	if (argc > 1) {
		(void) fprintf(stderr, gettext("too many arguments\n"));
		usage(B_FALSE);
	}

	/* open the snapshot */
	if ((snap = zfs_open(g_zfs, argv[0], ZFS_TYPE_SNAPSHOT)) == NULL)
		return (1);

	/* open the parent dataset */
	(void) strlcpy(parentname, argv[0], sizeof (parentname));
	verify((delim = strrchr(parentname, '@')) != NULL);
	*delim = '\0';
	if ((zhp = zfs_open(g_zfs, parentname, ZFS_TYPE_DATASET)) == NULL) {
		zfs_close(snap);
		return (1);
	}

	/*
	 * Check for more recent snapshots and/or clones based on the presence
	 * of '-r' and '-R'.
	 */
	cb.cb_target = argv[0];
	cb.cb_create = zfs_prop_get_int(snap, ZFS_PROP_CREATETXG);
	cb.cb_first = B_TRUE;
	cb.cb_error = 0;

	if (cb.cb_create > 0)
		min_txg = cb.cb_create;

	if ((ret = zfs_iter_snapshots(zhp, B_FALSE, rollback_check, &cb,
	    min_txg, 0)) != 0)
		goto out;
	if ((ret = zfs_iter_bookmarks(zhp, rollback_check, &cb)) != 0)
		goto out;

	if ((ret = cb.cb_error) != 0)
		goto out;

	/*
	 * Rollback parent to the given snapshot.
	 */
	ret = zfs_rollback(zhp, snap, force);

out:
	zfs_close(snap);
	zfs_close(zhp);

	if (ret == 0)
		return (0);
	else
		return (1);
}