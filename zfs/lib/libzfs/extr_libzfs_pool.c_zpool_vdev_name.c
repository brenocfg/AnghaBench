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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  tmpbuf ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int PATH_BUF_LEN ; 
 int VDEV_NAME_FOLLOW_LINKS ; 
 int VDEV_NAME_GUID ; 
 int VDEV_NAME_PATH ; 
 int VDEV_NAME_TYPE_ID ; 
 char* VDEV_TYPE_DISK ; 
 char* VDEV_TYPE_RAIDZ ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_ID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_NOT_PRESENT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_NPARITY ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PATH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_WHOLE_DISK ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 char* realpath (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify (int) ; 
 char* zfs_strdup (int /*<<< orphan*/ *,char*) ; 
 char* zfs_strip_partition (char*) ; 
 char* zfs_strip_path (char*) ; 
 char* zpool_get_name (int /*<<< orphan*/ *) ; 

char *
zpool_vdev_name(libzfs_handle_t *hdl, zpool_handle_t *zhp, nvlist_t *nv,
    int name_flags)
{
	char *path, *type, *env;
	uint64_t value;
	char buf[PATH_BUF_LEN];
	char tmpbuf[PATH_BUF_LEN];

	/*
	 * vdev_name will be "root"/"root-0" for the root vdev, but it is the
	 * zpool name that will be displayed to the user.
	 */
	verify(nvlist_lookup_string(nv, ZPOOL_CONFIG_TYPE, &type) == 0);
	if (zhp != NULL && strcmp(type, "root") == 0)
		return (zfs_strdup(hdl, zpool_get_name(zhp)));

	env = getenv("ZPOOL_VDEV_NAME_PATH");
	if (env && (strtoul(env, NULL, 0) > 0 ||
	    !strncasecmp(env, "YES", 3) || !strncasecmp(env, "ON", 2)))
		name_flags |= VDEV_NAME_PATH;

	env = getenv("ZPOOL_VDEV_NAME_GUID");
	if (env && (strtoul(env, NULL, 0) > 0 ||
	    !strncasecmp(env, "YES", 3) || !strncasecmp(env, "ON", 2)))
		name_flags |= VDEV_NAME_GUID;

	env = getenv("ZPOOL_VDEV_NAME_FOLLOW_LINKS");
	if (env && (strtoul(env, NULL, 0) > 0 ||
	    !strncasecmp(env, "YES", 3) || !strncasecmp(env, "ON", 2)))
		name_flags |= VDEV_NAME_FOLLOW_LINKS;

	if (nvlist_lookup_uint64(nv, ZPOOL_CONFIG_NOT_PRESENT, &value) == 0 ||
	    name_flags & VDEV_NAME_GUID) {
		(void) nvlist_lookup_uint64(nv, ZPOOL_CONFIG_GUID, &value);
		(void) snprintf(buf, sizeof (buf), "%llu", (u_longlong_t)value);
		path = buf;
	} else if (nvlist_lookup_string(nv, ZPOOL_CONFIG_PATH, &path) == 0) {
		if (name_flags & VDEV_NAME_FOLLOW_LINKS) {
			char *rp = realpath(path, NULL);
			if (rp) {
				strlcpy(buf, rp, sizeof (buf));
				path = buf;
				free(rp);
			}
		}

		/*
		 * For a block device only use the name.
		 */
		if ((strcmp(type, VDEV_TYPE_DISK) == 0) &&
		    !(name_flags & VDEV_NAME_PATH)) {
			path = zfs_strip_path(path);
		}

		/*
		 * Remove the partition from the path it this is a whole disk.
		 */
		if (nvlist_lookup_uint64(nv, ZPOOL_CONFIG_WHOLE_DISK, &value)
		    == 0 && value && !(name_flags & VDEV_NAME_PATH)) {
			return (zfs_strip_partition(path));
		}
	} else {
		path = type;

		/*
		 * If it's a raidz device, we need to stick in the parity level.
		 */
		if (strcmp(path, VDEV_TYPE_RAIDZ) == 0) {
			verify(nvlist_lookup_uint64(nv, ZPOOL_CONFIG_NPARITY,
			    &value) == 0);
			(void) snprintf(buf, sizeof (buf), "%s%llu", path,
			    (u_longlong_t)value);
			path = buf;
		}

		/*
		 * We identify each top-level vdev by using a <type-id>
		 * naming convention.
		 */
		if (name_flags & VDEV_NAME_TYPE_ID) {
			uint64_t id;
			verify(nvlist_lookup_uint64(nv, ZPOOL_CONFIG_ID,
			    &id) == 0);
			(void) snprintf(tmpbuf, sizeof (tmpbuf), "%s-%llu",
			    path, (u_longlong_t)id);
			path = tmpbuf;
		}
	}

	return (zfs_strdup(hdl, path));
}