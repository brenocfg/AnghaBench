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
struct TYPE_3__ {char* member_0; char* zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  parent ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  EZFS_BADTYPE ; 
 int /*<<< orphan*/  EZFS_INVALIDNAME ; 
 int /*<<< orphan*/  EZFS_NOENT ; 
 scalar_t__ GLOBAL_ZONEID ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IOC_OBJSET_STATS ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_ZONED ; 
 scalar_t__ ZFS_TYPE_FILESYSTEM ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ getzoneid () ; 
 int /*<<< orphan*/ * make_dataset_handle (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ parent_name (char const*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ zfs_get_type (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zfs_standard_error (int /*<<< orphan*/ *,scalar_t__,char*) ; 

__attribute__((used)) static int
check_parents(libzfs_handle_t *hdl, const char *path, uint64_t *zoned,
    boolean_t accept_ancestor, int *prefixlen)
{
	zfs_cmd_t zc = {"\0"};
	char parent[ZFS_MAX_DATASET_NAME_LEN];
	char *slash;
	zfs_handle_t *zhp;
	char errbuf[1024];
	uint64_t is_zoned;

	(void) snprintf(errbuf, sizeof (errbuf),
	    dgettext(TEXT_DOMAIN, "cannot create '%s'"), path);

	/* get parent, and check to see if this is just a pool */
	if (parent_name(path, parent, sizeof (parent)) != 0) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "missing dataset name"));
		return (zfs_error(hdl, EZFS_INVALIDNAME, errbuf));
	}

	/* check to see if the pool exists */
	if ((slash = strchr(parent, '/')) == NULL)
		slash = parent + strlen(parent);
	(void) strncpy(zc.zc_name, parent, slash - parent);
	zc.zc_name[slash - parent] = '\0';
	if (zfs_ioctl(hdl, ZFS_IOC_OBJSET_STATS, &zc) != 0 &&
	    errno == ENOENT) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "no such pool '%s'"), zc.zc_name);
		return (zfs_error(hdl, EZFS_NOENT, errbuf));
	}

	/* check to see if the parent dataset exists */
	while ((zhp = make_dataset_handle(hdl, parent)) == NULL) {
		if (errno == ENOENT && accept_ancestor) {
			/*
			 * Go deeper to find an ancestor, give up on top level.
			 */
			if (parent_name(parent, parent, sizeof (parent)) != 0) {
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "no such pool '%s'"), zc.zc_name);
				return (zfs_error(hdl, EZFS_NOENT, errbuf));
			}
		} else if (errno == ENOENT) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "parent does not exist"));
			return (zfs_error(hdl, EZFS_NOENT, errbuf));
		} else
			return (zfs_standard_error(hdl, errno, errbuf));
	}

	is_zoned = zfs_prop_get_int(zhp, ZFS_PROP_ZONED);
	if (zoned != NULL)
		*zoned = is_zoned;

	/* we are in a non-global zone, but parent is in the global zone */
	if (getzoneid() != GLOBAL_ZONEID && !is_zoned) {
		(void) zfs_standard_error(hdl, EPERM, errbuf);
		zfs_close(zhp);
		return (-1);
	}

	/* make sure parent is a filesystem */
	if (zfs_get_type(zhp) != ZFS_TYPE_FILESYSTEM) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "parent is not a filesystem"));
		(void) zfs_error(hdl, EZFS_BADTYPE, errbuf);
		zfs_close(zhp);
		return (-1);
	}

	zfs_close(zhp);
	if (prefixlen != NULL)
		*prefixlen = strlen(parent);
	return (0);
}