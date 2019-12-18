#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
typedef  int uint64_t ;
struct stat64 {scalar_t__ st_size; } ;
struct TYPE_9__ {char* zprl_type; int zprl_children; int zprl_parity; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ replication_level_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  long long int64_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int B_FALSE ; 
 scalar_t__ B_TRUE ; 
 scalar_t__ MAXOFFSET_T ; 
 int /*<<< orphan*/  O_RDONLY ; 
 char* VDEV_TYPE_HOLE ; 
 char* VDEV_TYPE_RAIDZ ; 
 char* VDEV_TYPE_REPLACING ; 
 char* VDEV_TYPE_SPARE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_IS_LOG ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_NPARITY ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PATH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 scalar_t__ ZPOOL_FUZZ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int fstat64_blk (int,struct stat64*) ; 
 int /*<<< orphan*/  gettext (char*) ; 
 scalar_t__ is_raidz_mirror (TYPE_1__*,TYPE_1__*,TYPE_1__**,TYPE_1__**) ; 
 scalar_t__ labs (long long) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,size_t*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* safe_malloc (int) ; 
 int stat64 (char*,struct stat64*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  vdev_error (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  verify (int) ; 

__attribute__((used)) static replication_level_t *
get_replication(nvlist_t *nvroot, boolean_t fatal)
{
	nvlist_t **top;
	uint_t t, toplevels;
	nvlist_t **child;
	uint_t c, children;
	nvlist_t *nv;
	char *type;
	replication_level_t lastrep = {0};
	replication_level_t rep;
	replication_level_t *ret;
	replication_level_t *raidz, *mirror;
	boolean_t dontreport;

	ret = safe_malloc(sizeof (replication_level_t));

	verify(nvlist_lookup_nvlist_array(nvroot, ZPOOL_CONFIG_CHILDREN,
	    &top, &toplevels) == 0);

	for (t = 0; t < toplevels; t++) {
		uint64_t is_log = B_FALSE;

		nv = top[t];

		/*
		 * For separate logs we ignore the top level vdev replication
		 * constraints.
		 */
		(void) nvlist_lookup_uint64(nv, ZPOOL_CONFIG_IS_LOG, &is_log);
		if (is_log)
			continue;

		/* Ignore holes introduced by removing aux devices */
		verify(nvlist_lookup_string(nv, ZPOOL_CONFIG_TYPE, &type) == 0);
		if (strcmp(type, VDEV_TYPE_HOLE) == 0)
			continue;

		if (nvlist_lookup_nvlist_array(nv, ZPOOL_CONFIG_CHILDREN,
		    &child, &children) != 0) {
			/*
			 * This is a 'file' or 'disk' vdev.
			 */
			rep.zprl_type = type;
			rep.zprl_children = 1;
			rep.zprl_parity = 0;
		} else {
			int64_t vdev_size;

			/*
			 * This is a mirror or RAID-Z vdev.  Go through and make
			 * sure the contents are all the same (files vs. disks),
			 * keeping track of the number of elements in the
			 * process.
			 *
			 * We also check that the size of each vdev (if it can
			 * be determined) is the same.
			 */
			rep.zprl_type = type;
			rep.zprl_children = 0;

			if (strcmp(type, VDEV_TYPE_RAIDZ) == 0) {
				verify(nvlist_lookup_uint64(nv,
				    ZPOOL_CONFIG_NPARITY,
				    &rep.zprl_parity) == 0);
				assert(rep.zprl_parity != 0);
			} else {
				rep.zprl_parity = 0;
			}

			/*
			 * The 'dontreport' variable indicates that we've
			 * already reported an error for this spec, so don't
			 * bother doing it again.
			 */
			type = NULL;
			dontreport = 0;
			vdev_size = -1LL;
			for (c = 0; c < children; c++) {
				nvlist_t *cnv = child[c];
				char *path;
				struct stat64 statbuf;
				int64_t size = -1LL;
				char *childtype;
				int fd, err;

				rep.zprl_children++;

				verify(nvlist_lookup_string(cnv,
				    ZPOOL_CONFIG_TYPE, &childtype) == 0);

				/*
				 * If this is a replacing or spare vdev, then
				 * get the real first child of the vdev: do this
				 * in a loop because replacing and spare vdevs
				 * can be nested.
				 */
				while (strcmp(childtype,
				    VDEV_TYPE_REPLACING) == 0 ||
				    strcmp(childtype, VDEV_TYPE_SPARE) == 0) {
					nvlist_t **rchild;
					uint_t rchildren;

					verify(nvlist_lookup_nvlist_array(cnv,
					    ZPOOL_CONFIG_CHILDREN, &rchild,
					    &rchildren) == 0);
					assert(rchildren == 2);
					cnv = rchild[0];

					verify(nvlist_lookup_string(cnv,
					    ZPOOL_CONFIG_TYPE,
					    &childtype) == 0);
				}

				verify(nvlist_lookup_string(cnv,
				    ZPOOL_CONFIG_PATH, &path) == 0);

				/*
				 * If we have a raidz/mirror that combines disks
				 * with files, report it as an error.
				 */
				if (!dontreport && type != NULL &&
				    strcmp(type, childtype) != 0) {
					if (ret != NULL)
						free(ret);
					ret = NULL;
					if (fatal)
						vdev_error(gettext(
						    "mismatched replication "
						    "level: %s contains both "
						    "files and devices\n"),
						    rep.zprl_type);
					else
						return (NULL);
					dontreport = B_TRUE;
				}

				/*
				 * According to stat(2), the value of 'st_size'
				 * is undefined for block devices and character
				 * devices.  But there is no effective way to
				 * determine the real size in userland.
				 *
				 * Instead, we'll take advantage of an
				 * implementation detail of spec_size().  If the
				 * device is currently open, then we (should)
				 * return a valid size.
				 *
				 * If we still don't get a valid size (indicated
				 * by a size of 0 or MAXOFFSET_T), then ignore
				 * this device altogether.
				 */
				if ((fd = open(path, O_RDONLY)) >= 0) {
					err = fstat64_blk(fd, &statbuf);
					(void) close(fd);
				} else {
					err = stat64(path, &statbuf);
				}

				if (err != 0 ||
				    statbuf.st_size == 0 ||
				    statbuf.st_size == MAXOFFSET_T)
					continue;

				size = statbuf.st_size;

				/*
				 * Also make sure that devices and
				 * slices have a consistent size.  If
				 * they differ by a significant amount
				 * (~16MB) then report an error.
				 */
				if (!dontreport &&
				    (vdev_size != -1LL &&
				    (labs(size - vdev_size) >
				    ZPOOL_FUZZ))) {
					if (ret != NULL)
						free(ret);
					ret = NULL;
					if (fatal)
						vdev_error(gettext(
						    "%s contains devices of "
						    "different sizes\n"),
						    rep.zprl_type);
					else
						return (NULL);
					dontreport = B_TRUE;
				}

				type = childtype;
				vdev_size = size;
			}
		}

		/*
		 * At this point, we have the replication of the last toplevel
		 * vdev in 'rep'.  Compare it to 'lastrep' to see if it is
		 * different.
		 */
		if (lastrep.zprl_type != NULL) {
			if (is_raidz_mirror(&lastrep, &rep, &raidz, &mirror) ||
			    is_raidz_mirror(&rep, &lastrep, &raidz, &mirror)) {
				/*
				 * Accepted raidz and mirror when they can
				 * handle the same number of disk failures.
				 */
				if (raidz->zprl_parity !=
				    mirror->zprl_children - 1) {
					if (ret != NULL)
						free(ret);
					ret = NULL;
					if (fatal)
						vdev_error(gettext(
						    "mismatched replication "
						    "level: "
						    "%s and %s vdevs with "
						    "different redundancy, "
						    "%llu vs. %llu (%llu-way) "
						    "are present\n"),
						    raidz->zprl_type,
						    mirror->zprl_type,
						    raidz->zprl_parity,
						    mirror->zprl_children - 1,
						    mirror->zprl_children);
					else
						return (NULL);
				}
			} else if (strcmp(lastrep.zprl_type, rep.zprl_type) !=
			    0) {
				if (ret != NULL)
					free(ret);
				ret = NULL;
				if (fatal)
					vdev_error(gettext(
					    "mismatched replication level: "
					    "both %s and %s vdevs are "
					    "present\n"),
					    lastrep.zprl_type, rep.zprl_type);
				else
					return (NULL);
			} else if (lastrep.zprl_parity != rep.zprl_parity) {
				if (ret)
					free(ret);
				ret = NULL;
				if (fatal)
					vdev_error(gettext(
					    "mismatched replication level: "
					    "both %llu and %llu device parity "
					    "%s vdevs are present\n"),
					    lastrep.zprl_parity,
					    rep.zprl_parity,
					    rep.zprl_type);
				else
					return (NULL);
			} else if (lastrep.zprl_children != rep.zprl_children) {
				if (ret)
					free(ret);
				ret = NULL;
				if (fatal)
					vdev_error(gettext(
					    "mismatched replication level: "
					    "both %llu-way and %llu-way %s "
					    "vdevs are present\n"),
					    lastrep.zprl_children,
					    rep.zprl_children,
					    rep.zprl_type);
				else
					return (NULL);
			}
		}
		lastrep = rep;
	}

	if (ret != NULL)
		*ret = rep;

	return (ret);
}