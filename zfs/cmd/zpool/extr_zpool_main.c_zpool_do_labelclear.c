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
typedef  int /*<<< orphan*/  vdev ;
struct stat {int dummy; } ;
typedef  int pool_state_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int ENOENT ; 
 scalar_t__ ENOTTY ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  O_RDWR ; 
#define  POOL_STATE_ACTIVE 133 
#define  POOL_STATE_DESTROYED 132 
#define  POOL_STATE_EXPORTED 131 
#define  POOL_STATE_L2CACHE 130 
#define  POOL_STATE_POTENTIALLY_ACTIVE 129 
#define  POOL_STATE_SPARE 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ optind ; 
 int optopt ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int zfs_append_partition (char*,int) ; 
 scalar_t__ zfs_dev_flush (int) ; 
 scalar_t__ zfs_dev_is_whole_disk (char*) ; 
 int zfs_resolve_shortname (char*,char*,int) ; 
 int zpool_clear_label (int) ; 
 int zpool_in_use (int /*<<< orphan*/ ,int,int*,char**,int /*<<< orphan*/ *) ; 
 char* zpool_pool_state_to_name (int) ; 
 scalar_t__ zpool_read_label (int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int
zpool_do_labelclear(int argc, char **argv)
{
	char vdev[MAXPATHLEN];
	char *name = NULL;
	struct stat st;
	int c, fd = -1, ret = 0;
	nvlist_t *config;
	pool_state_t state;
	boolean_t inuse = B_FALSE;
	boolean_t force = B_FALSE;

	/* check options */
	while ((c = getopt(argc, argv, "f")) != -1) {
		switch (c) {
		case 'f':
			force = B_TRUE;
			break;
		default:
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			usage(B_FALSE);
		}
	}

	argc -= optind;
	argv += optind;

	/* get vdev name */
	if (argc < 1) {
		(void) fprintf(stderr, gettext("missing vdev name\n"));
		usage(B_FALSE);
	}
	if (argc > 1) {
		(void) fprintf(stderr, gettext("too many arguments\n"));
		usage(B_FALSE);
	}

	/*
	 * Check if we were given absolute path and use it as is.
	 * Otherwise if the provided vdev name doesn't point to a file,
	 * try prepending expected disk paths and partition numbers.
	 */
	(void) strlcpy(vdev, argv[0], sizeof (vdev));
	if (vdev[0] != '/' && stat(vdev, &st) != 0) {
		int error;

		error = zfs_resolve_shortname(argv[0], vdev, MAXPATHLEN);
		if (error == 0 && zfs_dev_is_whole_disk(vdev)) {
			if (zfs_append_partition(vdev, MAXPATHLEN) == -1)
				error = ENOENT;
		}

		if (error || (stat(vdev, &st) != 0)) {
			(void) fprintf(stderr, gettext(
			    "failed to find device %s, try specifying absolute "
			    "path instead\n"), argv[0]);
			return (1);
		}
	}

	if ((fd = open(vdev, O_RDWR)) < 0) {
		(void) fprintf(stderr, gettext("failed to open %s: %s\n"),
		    vdev, strerror(errno));
		return (1);
	}

	/*
	 * Flush all dirty pages for the block device.  This should not be
	 * fatal when the device does not support BLKFLSBUF as would be the
	 * case for a file vdev.
	 */
	if ((zfs_dev_flush(fd) != 0) && (errno != ENOTTY))
		(void) fprintf(stderr, gettext("failed to invalidate "
		    "cache for %s: %s\n"), vdev, strerror(errno));

	if (zpool_read_label(fd, &config, NULL) != 0) {
		(void) fprintf(stderr,
		    gettext("failed to read label from %s\n"), vdev);
		ret = 1;
		goto errout;
	}
	nvlist_free(config);

	ret = zpool_in_use(g_zfs, fd, &state, &name, &inuse);
	if (ret != 0) {
		(void) fprintf(stderr,
		    gettext("failed to check state for %s\n"), vdev);
		ret = 1;
		goto errout;
	}

	if (!inuse)
		goto wipe_label;

	switch (state) {
	default:
	case POOL_STATE_ACTIVE:
	case POOL_STATE_SPARE:
	case POOL_STATE_L2CACHE:
		(void) fprintf(stderr, gettext(
		    "%s is a member (%s) of pool \"%s\"\n"),
		    vdev, zpool_pool_state_to_name(state), name);
		ret = 1;
		goto errout;

	case POOL_STATE_EXPORTED:
		if (force)
			break;
		(void) fprintf(stderr, gettext(
		    "use '-f' to override the following error:\n"
		    "%s is a member of exported pool \"%s\"\n"),
		    vdev, name);
		ret = 1;
		goto errout;

	case POOL_STATE_POTENTIALLY_ACTIVE:
		if (force)
			break;
		(void) fprintf(stderr, gettext(
		    "use '-f' to override the following error:\n"
		    "%s is a member of potentially active pool \"%s\"\n"),
		    vdev, name);
		ret = 1;
		goto errout;

	case POOL_STATE_DESTROYED:
		/* inuse should never be set for a destroyed pool */
		assert(0);
		break;
	}

wipe_label:
	ret = zpool_clear_label(fd);
	if (ret != 0) {
		(void) fprintf(stderr,
		    gettext("failed to clear label for %s\n"), vdev);
	}

errout:
	free(name);
	(void) close(fd);

	return (ret);
}