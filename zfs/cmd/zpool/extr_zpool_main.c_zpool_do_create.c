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
struct TYPE_3__ {char* fi_uname; } ;
typedef  TYPE_1__ zfeature_info_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  size_t spa_feature_t ;
typedef  int /*<<< orphan*/  propname ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 scalar_t__ ENOENT ; 
 scalar_t__ EZFS_INVALIDNAME ; 
 int MAXPATHLEN ; 
 size_t SPA_FEATURES ; 
 int /*<<< orphan*/  SPA_VERSION_FEATURES ; 
 char* VDEV_ALLOC_BIAS_DEDUP ; 
 char* VDEV_ALLOC_BIAS_LOG ; 
 char* VDEV_ALLOC_BIAS_SPECIAL ; 
 char* ZFS_FEATURE_DISABLED ; 
 char* ZFS_FEATURE_ENABLED ; 
 char* ZFS_MOUNTPOINT_LEGACY ; 
 char* ZFS_MOUNTPOINT_NONE ; 
 int /*<<< orphan*/  ZFS_PROP_MOUNTPOINT ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  ZPOOL_PROP_ALTROOT ; 
 int /*<<< orphan*/  ZPOOL_PROP_CACHEFILE ; 
 int /*<<< orphan*/  ZPOOL_PROP_TNAME ; 
 int /*<<< orphan*/  ZPOOL_PROP_VERSION ; 
 int add_prop_list (char*,char*,int /*<<< orphan*/ **,scalar_t__) ; 
 int /*<<< orphan*/  add_prop_list_default (char*,char*,int /*<<< orphan*/ **,scalar_t__) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 scalar_t__ libzfs_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * make_root_vdev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,scalar_t__,scalar_t__,int,char**) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  nvlist_remove_all (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  print_vdev_tree (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/ * readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 TYPE_1__* spa_feature_table ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  strtoull (char*,char**,int) ; 
 int /*<<< orphan*/  usage (scalar_t__) ; 
 int /*<<< orphan*/  zfs_allocatable_devs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_mount (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* zfs_prop_to_name (int /*<<< orphan*/ ) ; 
 int zfs_shareall (int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_create (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_name_to_prop (char*) ; 
 char* zpool_prop_to_name (int /*<<< orphan*/ ) ; 

int
zpool_do_create(int argc, char **argv)
{
	boolean_t force = B_FALSE;
	boolean_t dryrun = B_FALSE;
	boolean_t enable_all_pool_feat = B_TRUE;
	int c;
	nvlist_t *nvroot = NULL;
	char *poolname;
	char *tname = NULL;
	int ret = 1;
	char *altroot = NULL;
	char *mountpoint = NULL;
	nvlist_t *fsprops = NULL;
	nvlist_t *props = NULL;
	char *propval;

	/* check options */
	while ((c = getopt(argc, argv, ":fndR:m:o:O:t:")) != -1) {
		switch (c) {
		case 'f':
			force = B_TRUE;
			break;
		case 'n':
			dryrun = B_TRUE;
			break;
		case 'd':
			enable_all_pool_feat = B_FALSE;
			break;
		case 'R':
			altroot = optarg;
			if (add_prop_list(zpool_prop_to_name(
			    ZPOOL_PROP_ALTROOT), optarg, &props, B_TRUE))
				goto errout;
			if (add_prop_list_default(zpool_prop_to_name(
			    ZPOOL_PROP_CACHEFILE), "none", &props, B_TRUE))
				goto errout;
			break;
		case 'm':
			/* Equivalent to -O mountpoint=optarg */
			mountpoint = optarg;
			break;
		case 'o':
			if ((propval = strchr(optarg, '=')) == NULL) {
				(void) fprintf(stderr, gettext("missing "
				    "'=' for -o option\n"));
				goto errout;
			}
			*propval = '\0';
			propval++;

			if (add_prop_list(optarg, propval, &props, B_TRUE))
				goto errout;

			/*
			 * If the user is creating a pool that doesn't support
			 * feature flags, don't enable any features.
			 */
			if (zpool_name_to_prop(optarg) == ZPOOL_PROP_VERSION) {
				char *end;
				u_longlong_t ver;

				ver = strtoull(propval, &end, 10);
				if (*end == '\0' &&
				    ver < SPA_VERSION_FEATURES) {
					enable_all_pool_feat = B_FALSE;
				}
			}
			if (zpool_name_to_prop(optarg) == ZPOOL_PROP_ALTROOT)
				altroot = propval;
			break;
		case 'O':
			if ((propval = strchr(optarg, '=')) == NULL) {
				(void) fprintf(stderr, gettext("missing "
				    "'=' for -O option\n"));
				goto errout;
			}
			*propval = '\0';
			propval++;

			/*
			 * Mountpoints are checked and then added later.
			 * Uniquely among properties, they can be specified
			 * more than once, to avoid conflict with -m.
			 */
			if (0 == strcmp(optarg,
			    zfs_prop_to_name(ZFS_PROP_MOUNTPOINT))) {
				mountpoint = propval;
			} else if (add_prop_list(optarg, propval, &fsprops,
			    B_FALSE)) {
				goto errout;
			}
			break;
		case 't':
			/*
			 * Sanity check temporary pool name.
			 */
			if (strchr(optarg, '/') != NULL) {
				(void) fprintf(stderr, gettext("cannot create "
				    "'%s': invalid character '/' in temporary "
				    "name\n"), optarg);
				(void) fprintf(stderr, gettext("use 'zfs "
				    "create' to create a dataset\n"));
				goto errout;
			}

			if (add_prop_list(zpool_prop_to_name(
			    ZPOOL_PROP_TNAME), optarg, &props, B_TRUE))
				goto errout;
			if (add_prop_list_default(zpool_prop_to_name(
			    ZPOOL_PROP_CACHEFILE), "none", &props, B_TRUE))
				goto errout;
			tname = optarg;
			break;
		case ':':
			(void) fprintf(stderr, gettext("missing argument for "
			    "'%c' option\n"), optopt);
			goto badusage;
		case '?':
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			goto badusage;
		}
	}

	argc -= optind;
	argv += optind;

	/* get pool name and check number of arguments */
	if (argc < 1) {
		(void) fprintf(stderr, gettext("missing pool name argument\n"));
		goto badusage;
	}
	if (argc < 2) {
		(void) fprintf(stderr, gettext("missing vdev specification\n"));
		goto badusage;
	}

	poolname = argv[0];

	/*
	 * As a special case, check for use of '/' in the name, and direct the
	 * user to use 'zfs create' instead.
	 */
	if (strchr(poolname, '/') != NULL) {
		(void) fprintf(stderr, gettext("cannot create '%s': invalid "
		    "character '/' in pool name\n"), poolname);
		(void) fprintf(stderr, gettext("use 'zfs create' to "
		    "create a dataset\n"));
		goto errout;
	}

	/* pass off to make_root_vdev for bulk processing */
	nvroot = make_root_vdev(NULL, props, force, !force, B_FALSE, dryrun,
	    argc - 1, argv + 1);
	if (nvroot == NULL)
		goto errout;

	/* make_root_vdev() allows 0 toplevel children if there are spares */
	if (!zfs_allocatable_devs(nvroot)) {
		(void) fprintf(stderr, gettext("invalid vdev "
		    "specification: at least one toplevel vdev must be "
		    "specified\n"));
		goto errout;
	}

	if (altroot != NULL && altroot[0] != '/') {
		(void) fprintf(stderr, gettext("invalid alternate root '%s': "
		    "must be an absolute path\n"), altroot);
		goto errout;
	}

	/*
	 * Check the validity of the mountpoint and direct the user to use the
	 * '-m' mountpoint option if it looks like its in use.
	 */
	if (mountpoint == NULL ||
	    (strcmp(mountpoint, ZFS_MOUNTPOINT_LEGACY) != 0 &&
	    strcmp(mountpoint, ZFS_MOUNTPOINT_NONE) != 0)) {
		char buf[MAXPATHLEN];
		DIR *dirp;

		if (mountpoint && mountpoint[0] != '/') {
			(void) fprintf(stderr, gettext("invalid mountpoint "
			    "'%s': must be an absolute path, 'legacy', or "
			    "'none'\n"), mountpoint);
			goto errout;
		}

		if (mountpoint == NULL) {
			if (altroot != NULL)
				(void) snprintf(buf, sizeof (buf), "%s/%s",
				    altroot, poolname);
			else
				(void) snprintf(buf, sizeof (buf), "/%s",
				    poolname);
		} else {
			if (altroot != NULL)
				(void) snprintf(buf, sizeof (buf), "%s%s",
				    altroot, mountpoint);
			else
				(void) snprintf(buf, sizeof (buf), "%s",
				    mountpoint);
		}

		if ((dirp = opendir(buf)) == NULL && errno != ENOENT) {
			(void) fprintf(stderr, gettext("mountpoint '%s' : "
			    "%s\n"), buf, strerror(errno));
			(void) fprintf(stderr, gettext("use '-m' "
			    "option to provide a different default\n"));
			goto errout;
		} else if (dirp) {
			int count = 0;

			while (count < 3 && readdir(dirp) != NULL)
				count++;
			(void) closedir(dirp);

			if (count > 2) {
				(void) fprintf(stderr, gettext("mountpoint "
				    "'%s' exists and is not empty\n"), buf);
				(void) fprintf(stderr, gettext("use '-m' "
				    "option to provide a "
				    "different default\n"));
				goto errout;
			}
		}
	}

	/*
	 * Now that the mountpoint's validity has been checked, ensure that
	 * the property is set appropriately prior to creating the pool.
	 */
	if (mountpoint != NULL) {
		ret = add_prop_list(zfs_prop_to_name(ZFS_PROP_MOUNTPOINT),
		    mountpoint, &fsprops, B_FALSE);
		if (ret != 0)
			goto errout;
	}

	ret = 1;
	if (dryrun) {
		/*
		 * For a dry run invocation, print out a basic message and run
		 * through all the vdevs in the list and print out in an
		 * appropriate hierarchy.
		 */
		(void) printf(gettext("would create '%s' with the "
		    "following layout:\n\n"), poolname);

		print_vdev_tree(NULL, poolname, nvroot, 0, "", 0);
		print_vdev_tree(NULL, "dedup", nvroot, 0,
		    VDEV_ALLOC_BIAS_DEDUP, 0);
		print_vdev_tree(NULL, "special", nvroot, 0,
		    VDEV_ALLOC_BIAS_SPECIAL, 0);
		print_vdev_tree(NULL, "logs", nvroot, 0,
		    VDEV_ALLOC_BIAS_LOG, 0);

		ret = 0;
	} else {
		/*
		 * Hand off to libzfs.
		 */
		spa_feature_t i;
		for (i = 0; i < SPA_FEATURES; i++) {
			char propname[MAXPATHLEN];
			char *propval;
			zfeature_info_t *feat = &spa_feature_table[i];

			(void) snprintf(propname, sizeof (propname),
			    "feature@%s", feat->fi_uname);

			/*
			 * Only features contained in props will be enabled:
			 * remove from the nvlist every ZFS_FEATURE_DISABLED
			 * value and add every missing ZFS_FEATURE_ENABLED if
			 * enable_all_pool_feat is set.
			 */
			if (!nvlist_lookup_string(props, propname, &propval)) {
				if (strcmp(propval, ZFS_FEATURE_DISABLED) == 0)
					(void) nvlist_remove_all(props,
					    propname);
			} else if (enable_all_pool_feat) {
				ret = add_prop_list(propname,
				    ZFS_FEATURE_ENABLED, &props, B_TRUE);
				if (ret != 0)
					goto errout;
			}
		}

		ret = 1;
		if (zpool_create(g_zfs, poolname,
		    nvroot, props, fsprops) == 0) {
			zfs_handle_t *pool = zfs_open(g_zfs,
			    tname ? tname : poolname, ZFS_TYPE_FILESYSTEM);
			if (pool != NULL) {
				if (zfs_mount(pool, NULL, 0) == 0)
					ret = zfs_shareall(pool);
				zfs_close(pool);
			}
		} else if (libzfs_errno(g_zfs) == EZFS_INVALIDNAME) {
			(void) fprintf(stderr, gettext("pool name may have "
			    "been omitted\n"));
		}
	}

errout:
	nvlist_free(nvroot);
	nvlist_free(fsprops);
	nvlist_free(props);
	return (ret);
badusage:
	nvlist_free(fsprops);
	nvlist_free(props);
	usage(B_FALSE);
	return (2);
}