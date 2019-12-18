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
struct TYPE_3__ {char* sd_snapname; int /*<<< orphan*/  sd_nvl; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ snapdata_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  fsname ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EZFS_INVALIDNAME ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 int ZFS_TYPE_VOLUME ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_handle_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  zfs_snapshot_cb (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int zfs_snapshot_nvl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_validate_name (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
zfs_snapshot(libzfs_handle_t *hdl, const char *path, boolean_t recursive,
    nvlist_t *props)
{
	int ret;
	snapdata_t sd = { 0 };
	char fsname[ZFS_MAX_DATASET_NAME_LEN];
	char *cp;
	zfs_handle_t *zhp;
	char errbuf[1024];

	(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
	    "cannot snapshot %s"), path);

	if (!zfs_validate_name(hdl, path, ZFS_TYPE_SNAPSHOT, B_TRUE))
		return (zfs_error(hdl, EZFS_INVALIDNAME, errbuf));

	(void) strlcpy(fsname, path, sizeof (fsname));
	cp = strchr(fsname, '@');
	*cp = '\0';
	sd.sd_snapname = cp + 1;

	if ((zhp = zfs_open(hdl, fsname, ZFS_TYPE_FILESYSTEM |
	    ZFS_TYPE_VOLUME)) == NULL) {
		return (-1);
	}

	verify(nvlist_alloc(&sd.sd_nvl, NV_UNIQUE_NAME, 0) == 0);
	if (recursive) {
		(void) zfs_snapshot_cb(zfs_handle_dup(zhp), &sd);
	} else {
		fnvlist_add_boolean(sd.sd_nvl, path);
	}

	ret = zfs_snapshot_nvl(hdl, sd.sd_nvl, props);
	nvlist_free(sd.sd_nvl);
	zfs_close(zhp);
	return (ret);
}