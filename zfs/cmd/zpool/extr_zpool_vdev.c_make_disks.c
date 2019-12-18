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
typedef  size_t uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct stat64 {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISK_LABEL_WAIT ; 
 int EBUSY ; 
 int MAXPATHLEN ; 
 int O_EXCL ; 
 int O_RDWR ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDISK_ROOT ; 
 int /*<<< orphan*/  VDEV_TYPE_DISK ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_L2CACHE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PATH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_SPARES ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_WHOLE_DISK ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 char* gettext (char*) ; 
 scalar_t__ is_mpath_whole_disk (char*) ; 
 int /*<<< orphan*/  is_spare (int /*<<< orphan*/ *,char*) ; 
 int lstat64 (char*,struct stat64*) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,size_t*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/ * realpath (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  update_vdev_config_dev_strs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify (int) ; 
 int zero_label (char*) ; 
 int /*<<< orphan*/  zfs_append_partition (char*,int) ; 
 int zpool_label_disk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int zpool_label_disk_wait (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
make_disks(zpool_handle_t *zhp, nvlist_t *nv)
{
	nvlist_t **child;
	uint_t c, children;
	char *type, *path;
	char devpath[MAXPATHLEN];
	char udevpath[MAXPATHLEN];
	uint64_t wholedisk;
	struct stat64 statbuf;
	int is_exclusive = 0;
	int fd;
	int ret;

	verify(nvlist_lookup_string(nv, ZPOOL_CONFIG_TYPE, &type) == 0);

	if (nvlist_lookup_nvlist_array(nv, ZPOOL_CONFIG_CHILDREN,
	    &child, &children) != 0) {

		if (strcmp(type, VDEV_TYPE_DISK) != 0)
			return (0);

		/*
		 * We have a disk device.  If this is a whole disk write
		 * out the efi partition table, otherwise write zero's to
		 * the first 4k of the partition.  This is to ensure that
		 * libblkid will not misidentify the partition due to a
		 * magic value left by the previous filesystem.
		 */
		verify(!nvlist_lookup_string(nv, ZPOOL_CONFIG_PATH, &path));
		verify(!nvlist_lookup_uint64(nv, ZPOOL_CONFIG_WHOLE_DISK,
		    &wholedisk));

		if (!wholedisk) {
			/*
			 * Update device id string for mpath nodes (Linux only)
			 */
			if (is_mpath_whole_disk(path))
				update_vdev_config_dev_strs(nv);

			if (!is_spare(NULL, path))
				(void) zero_label(path);
			return (0);
		}

		if (realpath(path, devpath) == NULL) {
			ret = errno;
			(void) fprintf(stderr,
			    gettext("cannot resolve path '%s'\n"), path);
			return (ret);
		}

		/*
		 * Remove any previously existing symlink from a udev path to
		 * the device before labeling the disk.  This ensures that
		 * only newly created links are used.  Otherwise there is a
		 * window between when udev deletes and recreates the link
		 * during which access attempts will fail with ENOENT.
		 */
		strlcpy(udevpath, path, MAXPATHLEN);
		(void) zfs_append_partition(udevpath, MAXPATHLEN);

		fd = open(devpath, O_RDWR|O_EXCL);
		if (fd == -1) {
			if (errno == EBUSY)
				is_exclusive = 1;
		} else {
			(void) close(fd);
		}

		/*
		 * If the partition exists, contains a valid spare label,
		 * and is opened exclusively there is no need to partition
		 * it.  Hot spares have already been partitioned and are
		 * held open exclusively by the kernel as a safety measure.
		 *
		 * If the provided path is for a /dev/disk/ device its
		 * symbolic link will be removed, partition table created,
		 * and then block until udev creates the new link.
		 */
		if (!is_exclusive && !is_spare(NULL, udevpath)) {
			char *devnode = strrchr(devpath, '/') + 1;

			ret = strncmp(udevpath, UDISK_ROOT, strlen(UDISK_ROOT));
			if (ret == 0) {
				ret = lstat64(udevpath, &statbuf);
				if (ret == 0 && S_ISLNK(statbuf.st_mode))
					(void) unlink(udevpath);
			}

			/*
			 * When labeling a pool the raw device node name
			 * is provided as it appears under /dev/.
			 */
			if (zpool_label_disk(g_zfs, zhp, devnode) == -1)
				return (-1);

			/*
			 * Wait for udev to signal the device is available
			 * by the provided path.
			 */
			ret = zpool_label_disk_wait(udevpath, DISK_LABEL_WAIT);
			if (ret) {
				(void) fprintf(stderr,
				    gettext("missing link: %s was "
				    "partitioned but %s is missing\n"),
				    devnode, udevpath);
				return (ret);
			}

			ret = zero_label(udevpath);
			if (ret)
				return (ret);
		}

		/*
		 * Update the path to refer to the partition.  The presence of
		 * the 'whole_disk' field indicates to the CLI that we should
		 * chop off the partition number when displaying the device in
		 * future output.
		 */
		verify(nvlist_add_string(nv, ZPOOL_CONFIG_PATH, udevpath) == 0);

		/*
		 * Update device id strings for whole disks (Linux only)
		 */
		update_vdev_config_dev_strs(nv);

		return (0);
	}

	for (c = 0; c < children; c++)
		if ((ret = make_disks(zhp, child[c])) != 0)
			return (ret);

	if (nvlist_lookup_nvlist_array(nv, ZPOOL_CONFIG_SPARES,
	    &child, &children) == 0)
		for (c = 0; c < children; c++)
			if ((ret = make_disks(zhp, child[c])) != 0)
				return (ret);

	if (nvlist_lookup_nvlist_array(nv, ZPOOL_CONFIG_L2CACHE,
	    &child, &children) == 0)
		for (c = 0; c < children; c++)
			if ((ret = make_disks(zhp, child[c])) != 0)
				return (ret);

	return (0);
}